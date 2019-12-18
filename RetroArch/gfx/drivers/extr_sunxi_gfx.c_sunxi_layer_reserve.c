#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  uintptr_t uint32_t ;
struct TYPE_9__ {uintptr_t fb_id; uintptr_t layer_id; int layer_has_scaler; void* layer_format; scalar_t__ layer_scaler_is_enabled; int /*<<< orphan*/  fd_disp; int /*<<< orphan*/  framebuffer_paddr; } ;
typedef  TYPE_3__ sunxi_disp_t ;
struct TYPE_7__ {int width; int height; } ;
struct TYPE_8__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  seq; void* format; TYPE_1__ size; int /*<<< orphan*/ * addr; } ;
struct TYPE_10__ {int pipe; int alpha_en; int alpha_val; TYPE_2__ fb; } ;
typedef  TYPE_4__ __disp_layer_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_CMD_LAYER_GET_PARA ; 
 int /*<<< orphan*/  DISP_CMD_LAYER_REQUEST ; 
 int /*<<< orphan*/  DISP_CMD_LAYER_SET_PARA ; 
 void* DISP_FORMAT_ARGB8888 ; 
 uintptr_t DISP_LAYER_WORK_MODE_NORMAL ; 
 uintptr_t DISP_LAYER_WORK_MODE_SCALER ; 
 int /*<<< orphan*/  DISP_MOD_INTERLEAVED ; 
 int /*<<< orphan*/  DISP_SEQ_ARGB ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ sunxi_layer_change_work_mode (TYPE_3__*,uintptr_t) ; 

__attribute__((used)) static int sunxi_layer_reserve(sunxi_disp_t *ctx)
{
   __disp_layer_info_t layer_info;
   uint32_t tmp[4];

   /* try to allocate a layer */

   tmp[0] = ctx->fb_id;
   tmp[1] = DISP_LAYER_WORK_MODE_NORMAL;
   ctx->layer_id = ioctl(ctx->fd_disp, DISP_CMD_LAYER_REQUEST, &tmp);
   if (ctx->layer_id < 0)
      return -1;

   /* Initially set the layer configuration to something reasonable */

   tmp[0] = ctx->fb_id;
   tmp[1] = ctx->layer_id;
   tmp[2] = (uintptr_t)&layer_info;
   if (ioctl(ctx->fd_disp, DISP_CMD_LAYER_GET_PARA, tmp) < 0)
      return -1;

   /* the screen and overlay layers need to be in different pipes */
   layer_info.pipe      = 1;
   layer_info.alpha_en  = 1;
   layer_info.alpha_val = 255;

   layer_info.fb.addr[0] = ctx->framebuffer_paddr;
   layer_info.fb.size.width = 1;
   layer_info.fb.size.height = 1;
   layer_info.fb.format = DISP_FORMAT_ARGB8888;
   layer_info.fb.seq = DISP_SEQ_ARGB;
   layer_info.fb.mode = DISP_MOD_INTERLEAVED;

   tmp[0] = ctx->fb_id;
   tmp[1] = ctx->layer_id;
   tmp[2] = (uintptr_t)&layer_info;
   if (ioctl(ctx->fd_disp, DISP_CMD_LAYER_SET_PARA, tmp) < 0)
      return -1;

   /* Now probe the scaler mode to see if there is a free scaler available */
   if (sunxi_layer_change_work_mode(ctx, DISP_LAYER_WORK_MODE_SCALER) == 0)
      ctx->layer_has_scaler = 1;

   /* Revert back to normal mode */
   sunxi_layer_change_work_mode(ctx, DISP_LAYER_WORK_MODE_NORMAL);
   ctx->layer_scaler_is_enabled = 0;
   ctx->layer_format = DISP_FORMAT_ARGB8888;

   return ctx->layer_id;
}