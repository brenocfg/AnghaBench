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
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct TYPE_4__ {int /*<<< orphan*/  landscape_border_shadow_right; int /*<<< orphan*/  landscape_border_shadow_left; } ;
struct TYPE_5__ {scalar_t__ landscape_entry_margin; scalar_t__ margin; unsigned int nav_bar_layout_height; TYPE_1__ colors; scalar_t__ nav_bar_layout_width; } ;
typedef  TYPE_2__ materialui_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  menu_display_draw_quad (int /*<<< orphan*/ *,int,int,unsigned int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void materialui_render_landscape_border(
      materialui_handle_t *mui, video_frame_info_t *video_info,
      unsigned width, unsigned height, unsigned header_height, int x_offset)
{
   if (mui->landscape_entry_margin > mui->margin)
   {
      unsigned border_width  = mui->landscape_entry_margin - mui->margin;
      unsigned border_height = height - header_height - mui->nav_bar_layout_height;
      int left_x             = x_offset;
      int right_x            =
            x_offset + (int)width - (int)mui->landscape_entry_margin +
                  (int)mui->margin - (int)mui->nav_bar_layout_width;
      int y                  = (int)header_height;

      /* Draw left border */
      menu_display_draw_quad(
            video_info,
            left_x,
            y,
            border_width,
            border_height,
            width,
            height,
            mui->colors.landscape_border_shadow_left);

      /* Draw right border */
      menu_display_draw_quad(
            video_info,
            right_x,
            y,
            border_width,
            border_height,
            width,
            height,
            mui->colors.landscape_border_shadow_right);
   }
}