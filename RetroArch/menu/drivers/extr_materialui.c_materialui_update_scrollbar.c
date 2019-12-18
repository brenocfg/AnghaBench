#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int x; int y; scalar_t__ width; scalar_t__ height; scalar_t__ active; } ;
struct TYPE_5__ {scalar_t__ landscape_entry_margin; scalar_t__ margin; float scroll_y; float content_height; TYPE_1__ scrollbar; scalar_t__ nav_bar_layout_width; scalar_t__ nav_bar_layout_height; } ;
typedef  TYPE_2__ materialui_handle_t ;

/* Variables and functions */

__attribute__((used)) static void materialui_update_scrollbar(
      materialui_handle_t *mui,
      unsigned width, unsigned height,
      unsigned header_height, int x_offset)
{
   /* Do nothing if scrollbar is disabled */
   if (mui->scrollbar.active)
   {
      int view_height = (int)height - (int)header_height - (int)mui->nav_bar_layout_height;
      int y_max       = view_height + (int)header_height - (int)(mui->scrollbar.width + mui->scrollbar.height);

      /* Get X position */
      mui->scrollbar.x = x_offset + (int)width - (int)mui->scrollbar.width - (int)mui->nav_bar_layout_width;

      /* > Scrollbar must be offset by the current
       *   landscape border width when landscape optimisations
       *   are enabled */
      if (mui->landscape_entry_margin > mui->margin)
         mui->scrollbar.x -= (int)mui->landscape_entry_margin - (int)mui->margin;

      /* Get Y position */
      mui->scrollbar.y = (int)header_height + (int)(mui->scroll_y * (float)view_height / mui->content_height);

      /* > Apply vertical padding to improve visual appearance */
      mui->scrollbar.y += (int)mui->scrollbar.width;

      /* > Ensure we don't fall off the bottom of the screen... */
      mui->scrollbar.y = (mui->scrollbar.y > y_max) ? y_max : mui->scrollbar.y;
   }
}