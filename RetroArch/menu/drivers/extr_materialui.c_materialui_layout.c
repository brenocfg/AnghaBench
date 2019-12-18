#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char* battery_percent_str; char* timedate_str; scalar_t__ timedate_width; scalar_t__ battery_percent_width; } ;
struct TYPE_12__ {int glyph_width; int /*<<< orphan*/ * font; void* font_height; } ;
struct TYPE_14__ {int glyph_width; int /*<<< orphan*/ * font; void* font_height; } ;
struct TYPE_13__ {int glyph_width; int /*<<< orphan*/ * font; void* font_height; } ;
struct TYPE_15__ {TYPE_3__ hint; TYPE_5__ list; TYPE_4__ title; } ;
struct TYPE_11__ {int width; unsigned int divider_width; int selection_marker_width; int /*<<< orphan*/  location; } ;
struct TYPE_16__ {int is_portrait; scalar_t__ last_height; scalar_t__ last_width; int cursor_size; int dip_base_unit_size; int sys_bar_height; int title_bar_height; int header_shadow_height; int margin; int icon_size; int sys_bar_margin; int sys_bar_icon_size; unsigned int entry_divider_width; float last_scale_factor; int nav_bar_layout_width; int nav_bar_layout_height; int need_compute; TYPE_1__ sys_bar_cache; TYPE_6__ font_data; TYPE_2__ nav_bar; scalar_t__ last_auto_rotate_nav_bar; } ;
typedef  TYPE_7__ materialui_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  APPLICATION_SPECIAL_DIRECTORY_ASSETS_MATERIALUI_FONT ; 
 int /*<<< orphan*/  MUI_NAV_BAR_LOCATION_BOTTOM ; 
 int /*<<< orphan*/  MUI_NAV_BAR_LOCATION_RIGHT ; 
 void* font_driver_get_line_height (int /*<<< orphan*/ *,float) ; 
 unsigned int font_driver_get_message_width (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  materialui_update_list_view (TYPE_7__*) ; 
 void* menu_display_font (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  menu_display_font_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_display_set_header_height (unsigned int) ; 

__attribute__((used)) static void materialui_layout(materialui_handle_t *mui, bool video_is_threaded)
{
   int title_font_size;
   int list_font_size;
   int hint_font_size;
   unsigned new_header_height;

   mui->is_portrait          = mui->last_height >= mui->last_width;

   mui->cursor_size          = mui->dip_base_unit_size / 3;

   mui->sys_bar_height       = mui->dip_base_unit_size / 7;
   mui->title_bar_height     = mui->dip_base_unit_size / 3;
   new_header_height         = mui->sys_bar_height + mui->title_bar_height;

   title_font_size           = mui->dip_base_unit_size / 7;
   list_font_size            = mui->dip_base_unit_size / 9;
   hint_font_size            = mui->dip_base_unit_size / 11;

   mui->header_shadow_height = mui->dip_base_unit_size / 36;

   mui->margin               = mui->dip_base_unit_size / 9;
   mui->icon_size            = mui->dip_base_unit_size / 3;

   mui->sys_bar_margin       = mui->dip_base_unit_size / 12;
   mui->sys_bar_icon_size    = mui->dip_base_unit_size / 7;

   mui->entry_divider_width  = (mui->last_scale_factor > 1.0f) ?
         (unsigned)(mui->last_scale_factor + 0.5f) : 1;

   /* Note: We used to set scrollbar width here, but
    * since we now have several scrollbar parameters
    * that cannot be determined until materialui_compute_entries_box()
    * has been called, we delegate this to materialui_scrollbar_init() */

   /* Get navigation bar layout
    * > Normally drawn at the bottom of the screen,
    *   but in landscape orientations should be placed
    *   on the right hand side */
   mui->nav_bar.width                  = mui->dip_base_unit_size / 3;
   mui->nav_bar.divider_width          = mui->entry_divider_width;
   mui->nav_bar.selection_marker_width = mui->nav_bar.width / 16;

   if (!mui->is_portrait && mui->last_auto_rotate_nav_bar)
   {
      mui->nav_bar.location            = MUI_NAV_BAR_LOCATION_RIGHT;
      mui->nav_bar_layout_width        = mui->nav_bar.width;
      mui->nav_bar_layout_height       = 0;
   }
   else
   {
      mui->nav_bar.location            = MUI_NAV_BAR_LOCATION_BOTTOM;
      mui->nav_bar_layout_width        = 0;
      mui->nav_bar_layout_height       = mui->nav_bar.width;
   }

   /* We assume the average glyph aspect ratio is close to 3:4 */
   mui->font_data.title.glyph_width = (int)((title_font_size * (3.0f / 4.0f)) + 0.5f);
   mui->font_data.list.glyph_width  = (int)((list_font_size  * (3.0f / 4.0f)) + 0.5f);
   mui->font_data.hint.glyph_width  = (int)((hint_font_size  * (3.0f / 4.0f)) + 0.5f);

   menu_display_set_header_height(new_header_height);

   if (mui->font_data.title.font)
   {
      menu_display_font_free(mui->font_data.title.font);
      mui->font_data.title.font = NULL;
   }
   if (mui->font_data.list.font)
   {
      menu_display_font_free(mui->font_data.list.font);
      mui->font_data.list.font = NULL;
   }
   if (mui->font_data.hint.font)
   {
      menu_display_font_free(mui->font_data.hint.font);
      mui->font_data.hint.font = NULL;
   }

   mui->font_data.title.font = menu_display_font(
         APPLICATION_SPECIAL_DIRECTORY_ASSETS_MATERIALUI_FONT,
         title_font_size, video_is_threaded);

   mui->font_data.list.font  = menu_display_font(
         APPLICATION_SPECIAL_DIRECTORY_ASSETS_MATERIALUI_FONT,
         list_font_size, video_is_threaded);

   mui->font_data.hint.font  = menu_display_font(
         APPLICATION_SPECIAL_DIRECTORY_ASSETS_MATERIALUI_FONT,
         hint_font_size, video_is_threaded);

   if (mui->font_data.title.font)
   {
      /* Calculate a more realistic ticker_limit */
      unsigned title_char_width =
         font_driver_get_message_width(mui->font_data.title.font, "a", 1, 1);

      if (title_char_width)
         mui->font_data.title.glyph_width = title_char_width;

      /* Get font height */
      mui->font_data.title.font_height = font_driver_get_line_height(mui->font_data.title.font, 1.0f);
   }

   if (mui->font_data.list.font)
   {
      /* Calculate a more realistic ticker_limit */
      unsigned list_char_width =
         font_driver_get_message_width(mui->font_data.list.font, "a", 1, 1);

      if (list_char_width)
         mui->font_data.list.glyph_width = list_char_width;

      /* Get font height */
      mui->font_data.list.font_height = font_driver_get_line_height(mui->font_data.list.font, 1.0f);
   }

   if (mui->font_data.hint.font)
   {
      /* Calculate a more realistic ticker_limit */
      unsigned hint_char_width =
         font_driver_get_message_width(mui->font_data.hint.font, "t", 1, 1);

      if (hint_char_width)
         mui->font_data.hint.glyph_width = hint_char_width;

      /* Get font height */
      mui->font_data.hint.font_height = font_driver_get_line_height(mui->font_data.hint.font, 1.0f);
   }

   /* When updating the layout, the system bar
    * cache must be invalidated (since all text
    * size will change) */
   mui->sys_bar_cache.battery_percent_str[0] = '\0';
   mui->sys_bar_cache.battery_percent_width  = 0;
   mui->sys_bar_cache.timedate_str[0]        = '\0';
   mui->sys_bar_cache.timedate_width         = 0;

   materialui_update_list_view(mui);

   mui->need_compute = true;
}