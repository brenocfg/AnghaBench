#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t scroll_y; } ;
typedef  TYPE_1__ rgui_t ;
struct TYPE_6__ {int height; } ;

/* Variables and functions */
 size_t FONT_HEIGHT_STRIDE ; 
 int /*<<< orphan*/  MENU_ENTRIES_CTL_SET_START ; 
 int /*<<< orphan*/  menu_entries_ctl (int /*<<< orphan*/ ,size_t*) ; 
 size_t menu_entries_get_size () ; 
 size_t menu_navigation_get_selection () ; 
 int /*<<< orphan*/  rgui_scan_selected_entry_thumbnail (TYPE_1__*,int) ; 
 TYPE_3__ rgui_term_layout ; 
 int /*<<< orphan*/  rgui_update_menu_sublabel (TYPE_1__*) ; 

__attribute__((used)) static void rgui_navigation_set(void *data, bool scroll)
{
   size_t start;
   bool do_set_start              = false;
   size_t end                     = menu_entries_get_size();
   size_t selection               = menu_navigation_get_selection();
   rgui_t *rgui = (rgui_t*)data;

   if (!rgui)
      return;

   rgui_scan_selected_entry_thumbnail(rgui, false);
   rgui_update_menu_sublabel(rgui);

   if (!scroll)
      return;

   if (selection < rgui_term_layout.height /2)
   {
      start        = 0;
      do_set_start = true;
   }
   else if (selection >= (rgui_term_layout.height /2)
         && selection < (end - rgui_term_layout.height /2))
   {
      start        = selection - rgui_term_layout.height /2;
      do_set_start = true;
   }
   else if (selection >= (end - rgui_term_layout.height /2))
   {
      start        = end - rgui_term_layout.height;
      do_set_start = true;
   }

   if (do_set_start)
   {
      menu_entries_ctl(MENU_ENTRIES_CTL_SET_START, &start);
      rgui->scroll_y = start * FONT_HEIGHT_STRIDE;
   }
}