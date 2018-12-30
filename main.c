#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>


ALLEGRO_DISPLAY *display;
ALLEGRO_FILECHOOSER *save, *file_open;
ALLEGRO_BITMAP *drawing = NULL, *lefttool = NULL;
ALLEGRO_FONT *font;
ALLEGRO_COLOR selected_color, background_color;
int mouse_x, mouse_y, mouse_x2, mouse_y2, toolpick = 0;
bool done=false, start_draw=false;
float polygon_points[10];
float spline_points[8];
const char *path;
char *save_format;
void OpenCheck();
void FirstScreen();
void MainScreen();
void ToolBox();
void BackgroundSelect();
void SelectColor();
void CheckTool();
void Draws();
void NewFileCheck();
void OpenFile();
void SaveFile();

int main(int argc, char **argv) {
    OpenCheck();
    //FirstScreen();
    MainScreen();
    return 0;
}
void OpenCheck() {
    al_init();
    if (!al_init()) {
        al_show_native_message_box(NULL, "Something happened!", "Open Error", "Program starting error...", "Close", ALLEGRO_MESSAGEBOX_ERROR);
    }
}
void FirstScreen() {
    al_init_font_addon();
    al_init_ttf_addon();
    al_set_new_display_flags(ALLEGRO_NOFRAME);
    display = al_create_display(640, 480);
    al_clear_to_color(al_color_html("#FF9900"));
    font = al_load_font("/Library/Fonts/Futura.ttc", 40, 0);
    al_draw_text(font, al_color_html("#FFFFFF"), 320, 240, ALLEGRO_ALIGN_CENTER, "iPaint");
    al_draw_text(font, al_color_html("#FFFFFF"), 320, 280, ALLEGRO_ALIGN_CENTER, "Most Popular Drawing App :)");
    al_set_window_title(display, "iPaint");
    al_flip_display();
    al_rest(3.0);
    al_destroy_font(font);
    al_destroy_display(display);
}
void MainScreen() {
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    display = al_create_display(1280, 720);
    al_set_window_title(display, "iPaint");
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_flip_display();
    al_install_mouse();
    al_install_keyboard();
    ToolBox();
    Draws();
}
void ToolBox() {
    al_flip_display();
    al_init_image_addon();
    lefttool = al_load_bitmap("/Users/OnurSen/Desktop/Paint/Paint/images/back.png");
    if (!lefttool) {
        al_show_native_message_box(display, "Error", "Error", "Failed to load toolbox!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
    }
    al_draw_bitmap(lefttool, 1240, 0, 0);
    al_draw_filled_rectangle(1245, 555, 1265, 575, background_color);
    al_draw_filled_rectangle(1255, 560, 1275, 580, selected_color);
    al_flip_display();
}
void SelectColor() {
    if (mouse_x > 1241 && mouse_x < 1260) {
        if (mouse_y > 590 && mouse_y < 610)
            selected_color = al_map_rgb(255, 0, 0);
        else if (mouse_y > 616 && mouse_y < 630)
            selected_color = al_map_rgb(255, 255, 0);
        else if (mouse_y > 632 && mouse_y < 646)
            selected_color = al_map_rgb(0, 255, 0);
        else if (mouse_y > 652 && mouse_y < 666)
            selected_color = al_map_rgb(121, 0, 0);
        else if (mouse_y > 672 && mouse_y < 686)
            selected_color = al_map_rgb(255, 255, 255);
        else if (mouse_y > 690 && mouse_y < 704)
            selected_color = al_map_rgb(149, 149, 149);
    }
    else if (mouse_x > 1263 && mouse_x < 1279) {
        if (mouse_y > 590 && mouse_y < 610)
            selected_color = al_map_rgb(0, 140, 255);
        else if (mouse_y > 616 && mouse_y < 630)
            selected_color = al_map_rgb(255, 0, 255);
        else if (mouse_y > 632 && mouse_y < 646)
            selected_color = al_map_rgb(46, 49, 146);
        else if (mouse_y > 652 && mouse_y < 666)
            selected_color = al_map_rgb(0, 94, 32);
        else if (mouse_y > 672 && mouse_y < 686)
            selected_color = al_map_rgb(215, 215, 215);
        else if (mouse_y > 690 && mouse_y < 704)
            selected_color = al_map_rgb(0, 0, 0);
    }
}
void BackgroundSelect() {
    if (mouse_x > 1241 && mouse_x < 1260) {
        if (mouse_y > 590 && mouse_y < 610)
            background_color = al_map_rgb(255, 0, 0);
        else if (mouse_y > 616 && mouse_y < 630)
            background_color = al_map_rgb(255, 255, 0);
        else if (mouse_y > 632 && mouse_y < 646)
            background_color = al_map_rgb(0, 255, 0);
        else if (mouse_y > 652 && mouse_y < 666)
            background_color = al_map_rgb(121, 0, 0);
        else if (mouse_y > 672 && mouse_y < 686)
            background_color = al_map_rgb(255, 255, 255);
        else if (mouse_y > 690 && mouse_y < 704)
            background_color = al_map_rgb(149, 149, 149);
    }
    else if (mouse_x > 1263 && mouse_x < 1279) {
        if (mouse_y > 590 && mouse_y < 610)
            background_color = al_map_rgb(0, 140, 255);
        else if (mouse_y > 616 && mouse_y < 630)
            background_color = al_map_rgb(255, 0, 255);
        else if (mouse_y > 632 && mouse_y < 646)
            background_color = al_map_rgb(46, 49, 146);
        else if (mouse_y > 652 && mouse_y < 666)
            background_color = al_map_rgb(0, 94, 32);
        else if (mouse_y > 672 && mouse_y < 686)
            background_color = al_map_rgb(215, 215, 215);
        else if (mouse_y > 690 && mouse_y < 704)
            background_color = al_map_rgb(0, 0, 0);
    }
}
void Draws() {
    al_init_primitives_addon();
    drawing = al_create_bitmap(1240, 720);
    ALLEGRO_EVENT_QUEUE *event_que = NULL;
    event_que = al_create_event_queue();
    al_register_event_source(event_que,al_get_display_event_source(display));
    al_register_event_source(event_que,al_get_keyboard_event_source());
    al_register_event_source(event_que,al_get_mouse_event_source());
    while (!done) {
        ALLEGRO_EVENT events;
        al_wait_for_event(event_que, &events);
        if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            done = true;
        }
        if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if (events.mouse.button & 1) {
                mouse_x = events.mouse.x;
                mouse_y = events.mouse.y;
                start_draw=false;
                if (mouse_x > 1240 && mouse_x < 1280) {
                    if (mouse_y > 5 && mouse_y < 20)
                        NewFileCheck();
                    else if (mouse_y > 30 && mouse_y < 45)
                        OpenFile();
                    else if (mouse_y > 55 && mouse_y < 70)
                        SaveFile();
                    else if (mouse_y > 80 && mouse_y < 110)
                        toolpick = 1;
                    else if (mouse_y > 120 && mouse_y < 150)
                        toolpick = 2;
                    else if (mouse_y > 160 && mouse_y < 195)
                        toolpick = 3;
                    else if (mouse_y > 205 && mouse_y < 245)
                        toolpick = 4;
                    else if (mouse_y > 265 && mouse_y < 305)
                        toolpick = 5;
                    else if (mouse_y > 320 && mouse_y < 360)
                        toolpick = 6;
                    else if (mouse_y > 375 && mouse_y < 415)
                        toolpick = 7;
                    else if (mouse_y > 425 && mouse_y < 455)
                        toolpick = 8;
                    else if (mouse_y > 470 && mouse_y < 500)
                        toolpick = 9;
                    else if (mouse_y > 515 && mouse_y < 545)
                        toolpick = 10;
                    else if (mouse_y > 590 && mouse_y < 710) {
                        SelectColor();
                        al_flip_display();
                        al_draw_filled_rectangle(1245, 555, 1265, 575, background_color);
                        al_draw_filled_rectangle(1255, 560, 1275, 580, selected_color);
                        al_flip_display();
                        toolpick = toolpick;
                    }
                    else
                        toolpick = 0;
                }
            }
            else if (events.mouse.button & 2) {
                BackgroundSelect();
                al_set_target_bitmap(drawing);
                al_set_target_bitmap(al_get_backbuffer(display));
                al_draw_bitmap(drawing, 0, 0, 0);
                al_clear_to_color(background_color);
                al_flip_display();
                ToolBox();
            }
        }
        if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            if (events.mouse.button & 1) {
                mouse_x2 = events.mouse.x;
                mouse_y2 = events.mouse.y;
                if (mouse_x < 1240)
                    start_draw = true;
            }
        }
        if (events.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (events.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                done = true;
            }
        }
        if (start_draw) {
            al_clear_to_color(al_map_rgb(255, 255, 255));
            al_flip_display();
            al_set_target_bitmap(drawing);
                switch (toolpick) {
                    case 1:
                        al_draw_line(mouse_x, mouse_y, events.mouse.x, events.mouse.y, selected_color, 1);
                        break;
                    case 2:
                        if (mouse_x >= mouse_x2-20 && mouse_x <= mouse_x2+20)
                            al_draw_triangle(mouse_x, mouse_y, mouse_x2, mouse_y2, mouse_x2+100, events.mouse.y/2, selected_color, 1);
                        else
                            al_draw_triangle(mouse_x, mouse_y, mouse_x2, mouse_y2, (mouse_x2+mouse_x)/2, events.mouse.y/2, selected_color, 1);
                        break;
                    case 3:
                        al_draw_rectangle(mouse_x, mouse_y, mouse_x2, mouse_y2, selected_color, 1);
                        break;
                    case 4:
                        polygon_points[0] = mouse_x;
                        polygon_points[1] = mouse_y;
                        polygon_points[2] = mouse_x+80;
                        polygon_points[3] = mouse_y+75;
                        polygon_points[4] = mouse_x+60;
                        polygon_points[5] = mouse_y+150;
                        polygon_points[6] = mouse_x+-60;
                        polygon_points[7] = mouse_y+150;
                        polygon_points[8] = mouse_x-80;
                        polygon_points[9] = mouse_y+75;
                        al_draw_polygon(polygon_points, 5, 1, selected_color, 1, 1);
                        break;
                    case 5:
                        if(mouse_y2>mouse_y)
                            al_draw_arc(mouse_x, mouse_y, mouse_y2-mouse_y, 1.5, 2, selected_color, 1);
                        else
                            al_draw_arc(mouse_x, mouse_y, mouse_y-mouse_y2, 4.5, 2, selected_color, 1);
                        break;
                    case 6:
                        spline_points[0] = mouse_x;
                        spline_points[1] = mouse_y;
                        spline_points[2] = mouse_x2+50;
                        spline_points[3] = mouse_y2+50;
                        spline_points[4] = mouse_x2+100;
                        spline_points[5] = mouse_y2+100;
                        spline_points[6] = mouse_x2;
                        spline_points[7] = mouse_y2;
                        al_draw_spline(spline_points, selected_color, 1);
                        break;
                    case 7:
                        al_draw_circle(mouse_x, mouse_y, mouse_y2-mouse_y, selected_color, 1);
                        break;
                    case 8:
                        al_draw_pieslice(mouse_x, mouse_y, mouse_y2-mouse_y, 1, 1, selected_color, 1);
                        break;
                    case 9:
                        al_draw_ellipse(mouse_x, mouse_y, mouse_x2-mouse_x, mouse_y2-mouse_y, selected_color, 1);
                        break;
                    case 10:
                        al_draw_filled_circle(mouse_x, mouse_y, 10, selected_color);
                        break;
                    default:
                        break;
                }
            al_set_target_bitmap(al_get_backbuffer(display));
            al_draw_bitmap(drawing, 0, 0, 0);
            al_flip_display();
            start_draw = false;
        }
    }
}
void NewFileCheck() {
    int i;
    i = al_show_native_message_box(display, "Contains will be lost!", "Are you sure ?", "Do you want to open a new file?", NULL, ALLEGRO_MESSAGEBOX_YES_NO);
    if (i == 1) {
        al_destroy_bitmap(drawing);
        drawing = al_create_bitmap(1240, 720);
        al_clear_to_color(al_map_rgb(255, 255, 255));
        al_flip_display();
        ToolBox();
    }
}
void OpenFile() {
    file_open = al_create_native_file_dialog("Users/OnurSen/Desktop/Paint/Paint/", "File Open", ".png", ALLEGRO_FILECHOOSER_PICTURES);
    al_show_native_file_dialog(display, file_open);
    path = al_get_native_file_dialog_path(file_open, 0);
    drawing = al_load_bitmap(path);
    al_flip_display();
    ToolBox();
    al_flip_display();
}
void SaveFile() {
    save = al_create_native_file_dialog("Users/OnurSen/Desktop/Paint/Paint/", "File Save", "*.*", ALLEGRO_FILECHOOSER_SAVE);
    al_show_native_file_dialog(display, save);
    path = al_get_native_file_dialog_path(save, 0);
    path = strcat(path, ".png");
    al_save_bitmap(path, drawing);
}
