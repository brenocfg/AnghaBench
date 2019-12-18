#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_4__* out; TYPE_1__* priv; } ;
typedef  TYPE_5__ VC_PACKETIZER_T ;
struct TYPE_13__ {int /*<<< orphan*/  frame_rate_den; int /*<<< orphan*/  frame_rate_num; int /*<<< orphan*/  aspect_ratio_den; int /*<<< orphan*/  aspect_ratio_num; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_6__ VC_PACKETIZER_MODULE_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_11__ {TYPE_3__* type; } ;
struct TYPE_9__ {int /*<<< orphan*/  frame_rate_den; int /*<<< orphan*/  frame_rate_num; int /*<<< orphan*/  par_den; int /*<<< orphan*/  par_num; int /*<<< orphan*/  visible_height; int /*<<< orphan*/  height; int /*<<< orphan*/  visible_width; int /*<<< orphan*/  width; } ;
struct TYPE_10__ {TYPE_2__ video; } ;
struct TYPE_8__ {TYPE_6__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mpgv_update_format( VC_PACKETIZER_T *p_ctx )
{
   VC_PACKETIZER_MODULE_T *module = p_ctx->priv->module;

   LOG_DEBUG(0, "mpgv format: width %i, height %i, rate %i/%i, ar %i/%i",
             module->width, module->height, module->frame_rate_num, module->frame_rate_den,
             module->aspect_ratio_num, module->aspect_ratio_den);

   p_ctx->out->type->video.width = p_ctx->out->type->video.visible_width = module->width;
   p_ctx->out->type->video.height = p_ctx->out->type->video.visible_height = module->height;
   p_ctx->out->type->video.par_num = module->aspect_ratio_num;
   p_ctx->out->type->video.par_den = module->aspect_ratio_den;
   p_ctx->out->type->video.frame_rate_num = module->frame_rate_num;
   p_ctx->out->type->video.frame_rate_den = module->frame_rate_den;
   return VC_CONTAINER_SUCCESS;
}