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
struct TYPE_4__ {uintptr_t layer_id; uintptr_t fb_id; int /*<<< orphan*/  fd_disp; } ;
typedef  TYPE_1__ sunxi_disp_t ;
struct TYPE_5__ {int mode; } ;
typedef  TYPE_2__ __disp_layer_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_CMD_LAYER_GET_PARA ; 
 int /*<<< orphan*/  DISP_CMD_LAYER_SET_PARA ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t*) ; 

__attribute__((used)) static int sunxi_layer_change_work_mode(sunxi_disp_t *ctx, int new_mode)
{
   __disp_layer_info_t layer_info;
   uint32_t tmp[4];

   if (ctx->layer_id < 0)
      return -1;

   tmp[0] = ctx->fb_id;
   tmp[1] = ctx->layer_id;
   tmp[2] = (uintptr_t)&layer_info;

   if (ioctl(ctx->fd_disp, DISP_CMD_LAYER_GET_PARA, tmp) < 0)
      return -1;

   layer_info.mode = new_mode;

   tmp[0] = ctx->fb_id;
   tmp[1] = ctx->layer_id;
   tmp[2] = (uintptr_t)&layer_info;
   return ioctl(ctx->fd_disp, DISP_CMD_LAYER_SET_PARA, tmp);
}