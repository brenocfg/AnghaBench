#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct menu_animation_ctx_entry {float* subject; float target_value; int /*<<< orphan*/ * userdata; void* tag; void* easing_enum; void* duration; int /*<<< orphan*/ * cb; } ;
struct TYPE_9__ {float cursor_alpha; int scroll_y_sidebar; } ;
struct TYPE_8__ {int header_height; int sidebar_entry_height; unsigned int footer_height; float sidebar_padding_vertical; } ;
struct TYPE_10__ {unsigned int categories_selection_ptr; unsigned int categories_active_idx_old; unsigned int system_tab_end; size_t* tabs; TYPE_2__ animations; TYPE_1__ dimensions; int /*<<< orphan*/  cursor_in_sidebar; int /*<<< orphan*/  cursor_in_sidebar_old; } ;
typedef  TYPE_3__ ozone_handle_t ;
typedef  void* menu_animation_ctx_tag ;

/* Variables and functions */
 void* ANIMATION_CURSOR_DURATION ; 
 void* EASING_OUT_QUAD ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_HORIZONTAL_MENU ; 
 int /*<<< orphan*/  MENU_SETTING_HORIZONTAL_MENU ; 
 int /*<<< orphan*/  menu_animation_kill_by_tag (void**) ; 
 int /*<<< orphan*/  menu_animation_push (struct menu_animation_ctx_entry*) ; 
 int /*<<< orphan*/  ozone_change_tab (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float ozone_get_selected_sidebar_y_position (TYPE_3__*) ; 
 float ozone_get_sidebar_height (TYPE_3__*) ; 
 int /*<<< orphan*/ * ozone_system_tabs_idx ; 
 int /*<<< orphan*/ * ozone_system_tabs_type ; 
 int /*<<< orphan*/  video_driver_get_size (int /*<<< orphan*/ *,unsigned int*) ; 

void ozone_sidebar_goto(ozone_handle_t *ozone, unsigned new_selection)
{
   unsigned video_info_height;

   struct menu_animation_ctx_entry entry;

   menu_animation_ctx_tag tag;

   float new_scroll;
   float selected_position_y;
   float current_selection_middle_onscreen;
   float bottom_boundary;
   float entries_middle;
   float entries_height;

   video_driver_get_size(NULL, &video_info_height);

   tag = (uintptr_t)ozone;

   if (ozone->categories_selection_ptr != new_selection)
   {
      ozone->categories_active_idx_old = ozone->categories_selection_ptr;
      ozone->categories_selection_ptr = new_selection;

      ozone->cursor_in_sidebar_old = ozone->cursor_in_sidebar;

      menu_animation_kill_by_tag(&tag);
   }

   /* Cursor animation */
   ozone->animations.cursor_alpha = 0.0f;

   entry.cb             = NULL;
   entry.duration       = ANIMATION_CURSOR_DURATION;
   entry.easing_enum    = EASING_OUT_QUAD;
   entry.subject        = &ozone->animations.cursor_alpha;
   entry.tag            = tag;
   entry.target_value   = 1.0f;
   entry.userdata       = NULL;

   menu_animation_push(&entry);

   /* Scroll animation */
   new_scroll                             = 0;
   selected_position_y                    = ozone_get_selected_sidebar_y_position(ozone);
   current_selection_middle_onscreen      = ozone->dimensions.header_height + 1 + ozone->animations.scroll_y_sidebar + selected_position_y + ozone->dimensions.sidebar_entry_height / 2;
   bottom_boundary                        = video_info_height - (ozone->dimensions.header_height + 1) - ozone->dimensions.footer_height;
   entries_middle                         = video_info_height/2;
   entries_height                         = ozone_get_sidebar_height(ozone);

   if (current_selection_middle_onscreen != entries_middle)
      new_scroll = ozone->animations.scroll_y_sidebar - (current_selection_middle_onscreen - entries_middle);

   if (new_scroll + entries_height < bottom_boundary)
      new_scroll = bottom_boundary - entries_height - ozone->dimensions.sidebar_padding_vertical;

   if (new_scroll > 0)
      new_scroll = 0;

   entry.cb = NULL;
   entry.duration = ANIMATION_CURSOR_DURATION;
   entry.easing_enum = EASING_OUT_QUAD;
   entry.subject = &ozone->animations.scroll_y_sidebar;
   entry.tag = tag;
   entry.target_value = new_scroll;
   entry.userdata = NULL;

   menu_animation_push(&entry);

   if (new_selection > ozone->system_tab_end)
   {
      ozone_change_tab(ozone, MENU_ENUM_LABEL_HORIZONTAL_MENU, MENU_SETTING_HORIZONTAL_MENU);
   }
   else
   {
      ozone_change_tab(ozone, ozone_system_tabs_idx[ozone->tabs[new_selection]], ozone_system_tabs_type[ozone->tabs[new_selection]]);
   }
}