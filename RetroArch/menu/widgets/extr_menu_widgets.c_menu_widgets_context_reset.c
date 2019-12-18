#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xmb_path ;
typedef  int /*<<< orphan*/  theme_path ;
struct TYPE_6__ {int video_font_size; } ;
struct TYPE_5__ {char* directory_assets; char* path_font; } ;
struct TYPE_7__ {TYPE_2__ floats; TYPE_1__ paths; } ;
typedef  TYPE_3__ settings_t ;
typedef  int /*<<< orphan*/  ozone_path ;
typedef  int /*<<< orphan*/  monochrome_png_path ;
typedef  int /*<<< orphan*/  menu_widgets_path ;
typedef  int /*<<< orphan*/  font_path ;

/* Variables and functions */
 size_t MENU_WIDGETS_ICON_HOURGLASS ; 
 int MENU_WIDGETS_ICON_LAST ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  TEXTURE_FILTER_LINEAR ; 
 int /*<<< orphan*/  TEXTURE_FILTER_MIPMAP_LINEAR ; 
 int /*<<< orphan*/  TEXTURE_FILTER_NEAREST ; 
 TYPE_3__* config_get_ptr () ; 
 int /*<<< orphan*/  fill_pathname_join (char*,char*,char*,int) ; 
 void* font_bold ; 
 int /*<<< orphan*/  font_driver_get_line_height (void*,int) ; 
 float font_driver_get_message_width (void*,char*,int,int) ; 
 void* font_regular ; 
 int generic_message_height ; 
 float glyph_width ; 
 int /*<<< orphan*/  line_height ; 
 void* menu_display_font_file (char*,int,int) ; 
 int /*<<< orphan*/  menu_display_reset_textures_list (char*,char*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char** menu_widgets_icons_names ; 
 scalar_t__* menu_widgets_icons_textures ; 
 unsigned int msg_queue_base_width ; 
 int msg_queue_default_rect_width ; 
 int msg_queue_glyph_width ; 
 int msg_queue_has_icons ; 
 float msg_queue_height ; 
 scalar_t__ msg_queue_icon ; 
 float msg_queue_icon_offset_y ; 
 scalar_t__ msg_queue_icon_outline ; 
 scalar_t__ msg_queue_icon_rect ; 
 float msg_queue_icon_size_x ; 
 float msg_queue_icon_size_y ; 
 float msg_queue_internal_icon_offset ; 
 float msg_queue_internal_icon_size ; 
 float msg_queue_rect_start_x ; 
 float msg_queue_regular_padding_x ; 
 float msg_queue_regular_text_base_y ; 
 float msg_queue_regular_text_start ; 
 float msg_queue_scissor_start_x ; 
 float msg_queue_spacing ; 
 float msg_queue_task_hourglass_x ; 
 float msg_queue_task_rect_start_x ; 
 int msg_queue_task_text_start_x ; 
 float msg_queue_text_scale_factor ; 
 int simple_widget_height ; 
 int simple_widget_padding ; 

void menu_widgets_context_reset(bool is_threaded,
      unsigned width, unsigned height)
{
   int i;
   char xmb_path[PATH_MAX_LENGTH];
   char monochrome_png_path[PATH_MAX_LENGTH];
   char menu_widgets_path[PATH_MAX_LENGTH];
   char theme_path[PATH_MAX_LENGTH];
   char ozone_path[PATH_MAX_LENGTH];
   char font_path[PATH_MAX_LENGTH];
   settings_t *settings = config_get_ptr();

   /* Textures paths */
   fill_pathname_join(
      menu_widgets_path,
      settings->paths.directory_assets,
      "menu_widgets",
      sizeof(menu_widgets_path)
   );

   fill_pathname_join(
      xmb_path,
      settings->paths.directory_assets,
      "xmb",
      sizeof(xmb_path)
   );

   /* Monochrome */
   fill_pathname_join(
      theme_path,
      xmb_path,
      "monochrome",
      sizeof(theme_path)
   );

   fill_pathname_join(
      monochrome_png_path,
      theme_path,
      "png",
      sizeof(monochrome_png_path)
   );

   /* Load textures */
   /* Icons */
   for (i = 0; i < MENU_WIDGETS_ICON_LAST; i++)
   {
      menu_display_reset_textures_list(menu_widgets_icons_names[i], monochrome_png_path, &menu_widgets_icons_textures[i], TEXTURE_FILTER_MIPMAP_LINEAR, NULL, NULL);
   }

   /* Message queue */
   menu_display_reset_textures_list("msg_queue_icon.png", menu_widgets_path, &msg_queue_icon, TEXTURE_FILTER_LINEAR, NULL, NULL);
   menu_display_reset_textures_list("msg_queue_icon_outline.png", menu_widgets_path, &msg_queue_icon_outline, TEXTURE_FILTER_LINEAR, NULL, NULL);
   menu_display_reset_textures_list("msg_queue_icon_rect.png", menu_widgets_path, &msg_queue_icon_rect, TEXTURE_FILTER_NEAREST, NULL, NULL);

   msg_queue_has_icons = msg_queue_icon && msg_queue_icon_outline && msg_queue_icon_rect;

   /* Fonts paths */
      fill_pathname_join(
      ozone_path,
      settings->paths.directory_assets,
      "ozone",
      sizeof(ozone_path)
   );

   /* Fonts */
   if (settings->paths.path_font[0] == '\0')
   {
      fill_pathname_join(font_path, ozone_path, "regular.ttf", sizeof(font_path));
      font_regular = menu_display_font_file(font_path, settings->floats.video_font_size, is_threaded);

      fill_pathname_join(font_path, ozone_path, "bold.ttf", sizeof(font_path));
      font_bold = menu_display_font_file(font_path, settings->floats.video_font_size, is_threaded);
   }
   else
   {
      font_regular = menu_display_font_file(settings->paths.path_font, settings->floats.video_font_size, is_threaded);
      font_bold = menu_display_font_file(settings->paths.path_font, settings->floats.video_font_size, is_threaded);
   }

   /* Metrics */
   simple_widget_padding   = settings->floats.video_font_size * 2/3;
   simple_widget_height    = settings->floats.video_font_size + simple_widget_padding;
   glyph_width             = font_driver_get_message_width(font_regular, "a", 1, 1);
   line_height             = font_driver_get_line_height(font_regular, 1);

   msg_queue_height                 = settings->floats.video_font_size * 2.5f;

   if (msg_queue_has_icons)
   {
      msg_queue_icon_size_y         = msg_queue_height * 1.2347826087f; /* original image is 280x284 */
      msg_queue_icon_size_x         = 0.98591549295f * msg_queue_icon_size_y;
   }
   else
   {
      msg_queue_icon_size_x         = 0;
      msg_queue_icon_size_y         = 0;
   }

   msg_queue_text_scale_factor      = 0.69f;
   msg_queue_base_width             = width / 4;
   msg_queue_spacing                = msg_queue_height / 3;
   msg_queue_glyph_width            = glyph_width * msg_queue_text_scale_factor;
   msg_queue_rect_start_x           = msg_queue_spacing + msg_queue_icon_size_x;
   msg_queue_internal_icon_size     = msg_queue_icon_size_y;
   msg_queue_internal_icon_offset   = (msg_queue_icon_size_y - msg_queue_internal_icon_size)/2;
   msg_queue_icon_offset_y          = (msg_queue_icon_size_y - msg_queue_height)/2;
   msg_queue_scissor_start_x        = msg_queue_spacing + msg_queue_icon_size_x - (msg_queue_icon_size_x * 0.28928571428f);
   msg_queue_default_rect_width     = msg_queue_glyph_width * 40;

   if (msg_queue_has_icons)
      msg_queue_regular_padding_x   = simple_widget_padding/2;
   else
      msg_queue_regular_padding_x   = simple_widget_padding;

   msg_queue_task_rect_start_x      = msg_queue_rect_start_x - msg_queue_icon_size_x;

   msg_queue_task_text_start_x      = msg_queue_task_rect_start_x + msg_queue_height/2;

   if (!menu_widgets_icons_textures[MENU_WIDGETS_ICON_HOURGLASS])
      msg_queue_task_text_start_x   -= msg_queue_glyph_width*2;

   msg_queue_regular_text_start     = msg_queue_rect_start_x + msg_queue_regular_padding_x;
   msg_queue_regular_text_base_y    = settings->floats.video_font_size * msg_queue_text_scale_factor + msg_queue_height/2;

   msg_queue_task_hourglass_x       = msg_queue_rect_start_x - msg_queue_icon_size_x;

   generic_message_height           = settings->floats.video_font_size * 2;
}