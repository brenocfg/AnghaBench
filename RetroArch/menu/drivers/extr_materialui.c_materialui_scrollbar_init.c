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
struct TYPE_4__ {int width; unsigned int height; int active; int dragged; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_5__ {int dip_base_unit_size; float content_height; TYPE_1__ scrollbar; scalar_t__ nav_bar_layout_height; } ;
typedef  TYPE_2__ materialui_handle_t ;

/* Variables and functions */

__attribute__((used)) static void materialui_scrollbar_init(
      materialui_handle_t* mui,
      unsigned width, unsigned height, unsigned header_height)
{
   int view_height = (int)height - (int)header_height - (int)mui->nav_bar_layout_height;
   int scrollbar_height;

   /* Set initial defaults */
   mui->scrollbar.width   = mui->dip_base_unit_size / 36;
   mui->scrollbar.height  = 0;
   mui->scrollbar.x       = 0;
   mui->scrollbar.y       = 0;
   mui->scrollbar.active  = false;
   mui->scrollbar.dragged = false;

   /* If current window is too small to show any content
    * (unlikely) or all entries currently fit on a single
    * screen, scrollbar is disabled - can return immediately */
   if ((view_height <= 0) ||
       (mui->content_height <= (float)view_height))
      return;

   /* If we pass the above check, scrollbar is enabled */
   mui->scrollbar.active = true;

   /* Get scrollbar height */
   scrollbar_height = (int)((float)(view_height * view_height) / mui->content_height);

   /* > Apply vertical padding to improve visual appearance */
   scrollbar_height -= (int)mui->scrollbar.width * 2;

   /* > If the scrollbar is extremely short, display
    *   it as a square */
   if (scrollbar_height < (int)mui->scrollbar.width)
      scrollbar_height = (int)mui->scrollbar.width;

   mui->scrollbar.height = (unsigned)scrollbar_height;

   /* X and Y position are dynamic, and must be
    * set elsewhere */
}