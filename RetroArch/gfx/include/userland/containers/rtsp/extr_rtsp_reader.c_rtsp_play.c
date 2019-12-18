#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VC_CONTAINER_TRACK_MODULE_T ;
struct TYPE_8__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_9__ {int /*<<< orphan*/  header_list; } ;
typedef  TYPE_3__ VC_CONTAINER_MODULE_T ;
struct TYPE_7__ {TYPE_3__* module; } ;

/* Variables and functions */
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ rtsp_read_response (TYPE_2__*) ; 
 scalar_t__ rtsp_send_play_request (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtsp_store_rtp_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T rtsp_play( VC_CONTAINER_T *p_ctx,
      VC_CONTAINER_TRACK_MODULE_T *t_module )
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;

   status = rtsp_send_play_request(p_ctx, t_module);
   if (status != VC_CONTAINER_SUCCESS) return status;
   status = rtsp_read_response(p_ctx);
   if (status != VC_CONTAINER_SUCCESS) return status;

   rtsp_store_rtp_info(module->header_list, t_module);

   return status;
}