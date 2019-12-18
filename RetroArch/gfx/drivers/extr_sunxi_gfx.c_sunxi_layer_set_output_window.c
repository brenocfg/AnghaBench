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
typedef  uintptr_t uint32_t ;
struct TYPE_4__ {scalar_t__ layer_id; int layer_win_x; int layer_win_y; uintptr_t fb_id; int /*<<< orphan*/  fd_disp; } ;
typedef  TYPE_1__ sunxi_disp_t ;
struct TYPE_5__ {int member_0; int member_1; int member_2; int member_3; } ;
typedef  TYPE_2__ __disp_rect_t ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_CMD_LAYER_SET_SCN_WINDOW ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t**) ; 

__attribute__((used)) static int sunxi_layer_set_output_window(sunxi_disp_t *ctx, int x, int y, int w, int h)
{
   __disp_rect_t win_rect = { x, y, w, h };
   uint32_t tmp[4];

   if (ctx->layer_id < 0 || w <= 0 || h <= 0)
      return -1;

   /* Save the new non-adjusted window position */
   ctx->layer_win_x = x;
   ctx->layer_win_y = y;

   tmp[0] = ctx->fb_id;
   tmp[1] = ctx->layer_id;
   tmp[2] = (uintptr_t)&win_rect;
   return ioctl(ctx->fd_disp, DISP_CMD_LAYER_SET_SCN_WINDOW, &tmp);
}