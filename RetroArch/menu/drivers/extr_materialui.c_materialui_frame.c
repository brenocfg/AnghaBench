#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_60__   TYPE_9__ ;
typedef  struct TYPE_59__   TYPE_8__ ;
typedef  struct TYPE_58__   TYPE_7__ ;
typedef  struct TYPE_57__   TYPE_6__ ;
typedef  struct TYPE_56__   TYPE_5__ ;
typedef  struct TYPE_55__   TYPE_4__ ;
typedef  struct TYPE_54__   TYPE_42__ ;
typedef  struct TYPE_53__   TYPE_3__ ;
typedef  struct TYPE_52__   TYPE_2__ ;
typedef  struct TYPE_51__   TYPE_1__ ;
typedef  struct TYPE_50__   TYPE_16__ ;
typedef  struct TYPE_49__   TYPE_15__ ;
typedef  struct TYPE_48__   TYPE_14__ ;
typedef  struct TYPE_47__   TYPE_13__ ;
typedef  struct TYPE_46__   TYPE_12__ ;
typedef  struct TYPE_45__   TYPE_11__ ;
typedef  struct TYPE_44__   TYPE_10__ ;

/* Type definitions */
struct TYPE_48__ {unsigned int width; unsigned int height; scalar_t__ materialui_color_theme; } ;
typedef  TYPE_14__ video_frame_info_t ;
struct TYPE_60__ {scalar_t__ menu_ticker_type; } ;
struct TYPE_57__ {scalar_t__ menu_ticker_smooth; } ;
struct TYPE_49__ {TYPE_9__ uints; TYPE_6__ bools; } ;
typedef  TYPE_15__ settings_t ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_55__ {scalar_t__ vertices; } ;
struct TYPE_56__ {TYPE_4__ coords; } ;
struct TYPE_54__ {TYPE_5__ carr; } ;
struct TYPE_46__ {int /*<<< orphan*/  font; TYPE_42__ raster_block; } ;
struct TYPE_45__ {int /*<<< orphan*/  font; TYPE_42__ raster_block; } ;
struct TYPE_53__ {int /*<<< orphan*/  font; TYPE_42__ raster_block; } ;
struct TYPE_47__ {TYPE_12__ hint; TYPE_11__ list; TYPE_3__ title; } ;
struct TYPE_52__ {scalar_t__ type; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_51__ {int /*<<< orphan*/ * list; } ;
struct TYPE_44__ {int /*<<< orphan*/  screen_fade; int /*<<< orphan*/  list_highlighted_background; } ;
struct TYPE_59__ {int type_enum; int /*<<< orphan*/  idx; } ;
struct TYPE_58__ {int type_enum; int /*<<< orphan*/  idx; } ;
struct TYPE_50__ {scalar_t__ color_theme; float transition_x_offset; char* msgbox; TYPE_13__ font_data; TYPE_2__ pointer; TYPE_1__ textures; int /*<<< orphan*/  cursor_size; scalar_t__ mouse_show; TYPE_10__ colors; scalar_t__ nav_bar_layout_width; TYPE_8__ ticker; TYPE_7__ ticker_smooth; scalar_t__ use_smooth_ticker; } ;
typedef  TYPE_16__ materialui_handle_t ;
typedef  enum menu_animation_ticker_type { ____Placeholder_menu_animation_ticker_type } menu_animation_ticker_type ;
typedef  enum materialui_color_theme { ____Placeholder_materialui_color_theme } materialui_color_theme ;

/* Variables and functions */
 scalar_t__ MENU_POINTER_DISABLED ; 
 size_t MUI_TEXTURE_KEY_HOVER ; 
 size_t MUI_TEXTURE_POINTER ; 
 TYPE_15__* config_get_ptr () ; 
 int /*<<< orphan*/  font_driver_bind_block (int /*<<< orphan*/ ,TYPE_42__*) ; 
 int /*<<< orphan*/  font_driver_flush (unsigned int,unsigned int,int /*<<< orphan*/ ,TYPE_14__*) ; 
 int /*<<< orphan*/  materialui_colors_reset_transition_alpha (TYPE_16__*) ; 
 int /*<<< orphan*/  materialui_colors_set_transition_alpha (TYPE_16__*) ; 
 int /*<<< orphan*/  materialui_prepare_colors (TYPE_16__*,int) ; 
 int /*<<< orphan*/  materialui_render_background (TYPE_16__*,TYPE_14__*) ; 
 int /*<<< orphan*/  materialui_render_entry_touch_feedback (TYPE_16__*,TYPE_14__*,unsigned int,unsigned int,unsigned int,int,size_t) ; 
 int /*<<< orphan*/  materialui_render_header (TYPE_16__*,TYPE_14__*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  materialui_render_landscape_border (TYPE_16__*,TYPE_14__*,unsigned int,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  materialui_render_menu_list (TYPE_16__*,TYPE_14__*,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  materialui_render_messagebox (TYPE_16__*,TYPE_14__*,unsigned int,char*) ; 
 int /*<<< orphan*/  materialui_render_nav_bar (TYPE_16__*,TYPE_14__*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  materialui_render_selection_highlight (TYPE_16__*,TYPE_14__*,unsigned int,unsigned int,unsigned int,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  materialui_update_scrollbar (TYPE_16__*,unsigned int,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  menu_animation_get_ticker_idx () ; 
 int /*<<< orphan*/  menu_animation_get_ticker_pixel_idx () ; 
 int /*<<< orphan*/  menu_display_draw_cursor (TYPE_14__*,float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  menu_display_draw_keyboard (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_14__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  menu_display_draw_quad (TYPE_14__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int menu_display_get_header_height () ; 
 int /*<<< orphan*/  menu_display_set_viewport (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  menu_display_unset_viewport (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  menu_event_get_osk_grid () ; 
 int /*<<< orphan*/  menu_event_get_osk_ptr () ; 
 char* menu_input_dialog_get_buffer () ; 
 scalar_t__ menu_input_dialog_get_display_kb () ; 
 char* menu_input_dialog_get_label_buffer () ; 
 size_t menu_navigation_get_selection () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 

__attribute__((used)) static void materialui_frame(void *data, video_frame_info_t *video_info)
{
   materialui_handle_t *mui = (materialui_handle_t*)data;
   settings_t *settings     = config_get_ptr();
   unsigned width           = video_info->width;
   unsigned height          = video_info->height;
   unsigned header_height   = menu_display_get_header_height();
   size_t selection         = menu_navigation_get_selection();
   int list_x_offset;

   if (!mui || !settings)
      return;

   menu_display_set_viewport(width, height);

   /* Clear text */
   font_driver_bind_block(mui->font_data.title.font, &mui->font_data.title.raster_block);
   font_driver_bind_block(mui->font_data.list.font,  &mui->font_data.list.raster_block);
   font_driver_bind_block(mui->font_data.hint.font,  &mui->font_data.hint.raster_block);

   mui->font_data.title.raster_block.carr.coords.vertices = 0;
   mui->font_data.list.raster_block.carr.coords.vertices  = 0;
   mui->font_data.hint.raster_block.carr.coords.vertices  = 0;

   /* Update theme colours, if required */
   if (mui->color_theme != video_info->materialui_color_theme)
   {
      materialui_prepare_colors(mui, (enum materialui_color_theme)video_info->materialui_color_theme);
      mui->color_theme = (enum materialui_color_theme)video_info->materialui_color_theme;
   }

   /* Update line ticker(s) */
   mui->use_smooth_ticker = settings->bools.menu_ticker_smooth;

   if (mui->use_smooth_ticker)
   {
      mui->ticker_smooth.idx       = menu_animation_get_ticker_pixel_idx();
      mui->ticker_smooth.type_enum = (enum menu_animation_ticker_type)settings->uints.menu_ticker_type;
   }
   else
   {
      mui->ticker.idx       = menu_animation_get_ticker_idx();
      mui->ticker.type_enum = (enum menu_animation_ticker_type)settings->uints.menu_ticker_type;
   }

   /* Handle any transparency adjustments required
    * by menu transition animations */
   materialui_colors_set_transition_alpha(mui);

   /* Get x offset for list items, required by
    * menu transition 'slide' animations */
   list_x_offset = (int)(mui->transition_x_offset * (float)((int)width - (int)mui->nav_bar_layout_width));

   /* Draw background */
   materialui_render_background(mui, video_info);

   /* Draw landscape border
    * (does nothing in portrait mode, or if landscape
    * optimisations are disabled) */
   materialui_render_landscape_border(
         mui, video_info, width, height, header_height, list_x_offset);

   /* Draw 'highlighted entry' selection box */
   materialui_render_selection_highlight(
         mui, video_info, width, height, header_height, list_x_offset, selection,
         mui->colors.list_highlighted_background);

   /* Draw 'short press' touch feedback highlight */
   materialui_render_entry_touch_feedback(
         mui, video_info, width, height, header_height, list_x_offset, selection);

   /* Draw menu list
    * > Must update scrollbar draw position before
    *   list is rendered
    * > We handle the scrollbar in a separate step
    *   like this because we need to track its
    *   position in order to enable fast navigation
    *   via scrollbar 'dragging' */
   materialui_update_scrollbar(mui, width, height, header_height, list_x_offset);
   materialui_render_menu_list(mui, video_info, width, height, list_x_offset);

   /* Flush first layer of text
    * > Menu list only uses list and hint fonts */
   font_driver_flush(width, height, mui->font_data.list.font, video_info);
   font_driver_flush(width, height, mui->font_data.hint.font, video_info);

   mui->font_data.list.raster_block.carr.coords.vertices = 0;
   mui->font_data.hint.raster_block.carr.coords.vertices = 0;

   /* Draw title + system bar */
   materialui_render_header(mui, video_info, width, height);

   /* Draw navigation bar */
   materialui_render_nav_bar(mui, video_info, width, height);

   /* Flush second layer of text
    * > Title + system bar only use title and hint fonts */
   font_driver_flush(width, height, mui->font_data.title.font, video_info);
   font_driver_flush(width, height, mui->font_data.hint.font,  video_info);

   mui->font_data.title.raster_block.carr.coords.vertices = 0;
   mui->font_data.hint.raster_block.carr.coords.vertices  = 0;

   /* Handle onscreen keyboard */
   if (menu_input_dialog_get_display_kb())
   {
      char msg[255];
      const char *str   = menu_input_dialog_get_buffer();
      const char *label = menu_input_dialog_get_label_buffer();

      msg[0] = '\0';

      /* Darken screen */
      menu_display_draw_quad(video_info,
            0, 0, width, height, width, height, mui->colors.screen_fade);

      /* Draw message box */
      snprintf(msg, sizeof(msg), "%s\n%s", label, str);
      materialui_render_messagebox(mui, video_info, height / 4, msg);

      /* Draw onscreen keyboard */
      menu_display_draw_keyboard(
            mui->textures.list[MUI_TEXTURE_KEY_HOVER],
            mui->font_data.list.font,
            video_info,
            menu_event_get_osk_grid(), menu_event_get_osk_ptr(),
            0xFFFFFFFF);

      /* Flush message box & osk text
       * > Message box & osk only use list font */
      font_driver_flush(width, height, mui->font_data.list.font, video_info);
      mui->font_data.list.raster_block.carr.coords.vertices = 0;
   }

   /* Draw message box */
   if (!string_is_empty(mui->msgbox))
   {
      /* Darken screen */
      menu_display_draw_quad(video_info,
            0, 0, width, height, width, height, mui->colors.screen_fade);

      /* Draw message box */
      materialui_render_messagebox(mui, video_info, height / 2, mui->msgbox);
      mui->msgbox[0] = '\0';

      /* Flush message box text
       * > Message box only uses list font */
      font_driver_flush(width, height, mui->font_data.list.font, video_info);
      mui->font_data.list.raster_block.carr.coords.vertices = 0;
   }

   /* Draw mouse cursor */
   if (mui->mouse_show && (mui->pointer.type != MENU_POINTER_DISABLED))
   {
      float color_white[16]  = {
         1.0f, 1.0f, 1.0f, 1.0f,
         1.0f, 1.0f, 1.0f, 1.0f,
         1.0f, 1.0f, 1.0f, 1.0f,
         1.0f, 1.0f, 1.0f, 1.0f
      };

      menu_display_draw_cursor(
            video_info,
            color_white,
            mui->cursor_size,
            mui->textures.list[MUI_TEXTURE_POINTER],
            mui->pointer.x,
            mui->pointer.y,
            width,
            height);
   }

   /* Undo any transparency adjustments caused
    * by menu transition animations */
   materialui_colors_reset_transition_alpha(mui);

   /* Unbind fonts */
   font_driver_bind_block(mui->font_data.title.font, NULL);
   font_driver_bind_block(mui->font_data.list.font,  NULL);
   font_driver_bind_block(mui->font_data.hint.font,  NULL);

   menu_display_unset_viewport(width, height);
}