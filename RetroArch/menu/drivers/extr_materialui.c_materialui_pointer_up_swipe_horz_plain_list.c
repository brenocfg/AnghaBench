#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  menu_entry_t ;
struct TYPE_5__ {float content_height; scalar_t__ scroll_y; scalar_t__ nav_bar_layout_height; } ;
typedef  TYPE_1__ materialui_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ACTION_SCROLL_DOWN ; 
 int /*<<< orphan*/  MENU_ACTION_SCROLL_UP ; 
 int /*<<< orphan*/  MUI_ANIM_DURATION_SCROLL ; 
 int /*<<< orphan*/  materialui_animate_scroll (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int materialui_menu_entry_action (TYPE_1__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int materialui_pointer_up_swipe_horz_plain_list(
      materialui_handle_t *mui, menu_entry_t *entry,
      unsigned height, unsigned header_height, unsigned y,
      size_t selection, bool scroll_up)
{
   /* A swipe in the top half of the screen ascends/
    * descends the alphabet */
   if (y < (height >> 1))
      return materialui_menu_entry_action(
            mui, entry, selection,
            scroll_up ? MENU_ACTION_SCROLL_UP : MENU_ACTION_SCROLL_DOWN);
   /* A swipe in the bottom half of the screen scrolls
    * by 10% of the list size or one 'page', whichever
    * is largest */
   else
   {
      float content_height_fraction = mui->content_height * 0.1f;
      float display_height          = (int)height - (int)header_height - (int)mui->nav_bar_layout_height;
      float scroll_offset           = (display_height > content_height_fraction) ?
            display_height : content_height_fraction;

      materialui_animate_scroll(
            mui,
            mui->scroll_y + (scroll_up ? (scroll_offset * -1.0f) : scroll_offset),
            MUI_ANIM_DURATION_SCROLL);
   }

   return 0;
}