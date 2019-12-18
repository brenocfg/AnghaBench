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
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct TYPE_6__ {int /*<<< orphan*/  scrollbar; } ;
struct TYPE_5__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  active; } ;
struct TYPE_7__ {TYPE_2__ colors; TYPE_1__ scrollbar; } ;
typedef  TYPE_3__ materialui_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  menu_display_draw_quad (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void materialui_render_scrollbar(
      materialui_handle_t *mui,
      video_frame_info_t *video_info,
      unsigned width, unsigned height)
{
   /* Do nothing if scrollbar is disabled */
   if (!mui->scrollbar.active)
      return;

   /* Draw scrollbar */
   menu_display_draw_quad(
         video_info,
         mui->scrollbar.x,
         mui->scrollbar.y,
         mui->scrollbar.width,
         mui->scrollbar.height,
         width, height,
         mui->colors.scrollbar);
}