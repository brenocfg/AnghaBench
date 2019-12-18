#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int tracks_num; TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_8__ {unsigned int current_track; } ;
typedef  TYPE_3__ VC_CONTAINER_MODULE_T ;
struct TYPE_6__ {TYPE_3__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_BOX_TYPE_MVHD ; 
 int /*<<< orphan*/  MP4_BOX_TYPE_TRAK ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ mp4_write_box (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_write_box_moov( VC_CONTAINER_T *p_ctx )
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   unsigned int i;

   status = mp4_write_box(p_ctx, MP4_BOX_TYPE_MVHD);
   if(status != VC_CONTAINER_SUCCESS) return status;

   for(i = 0; i < p_ctx->tracks_num; i++)
   {
      module->current_track = i;
      status = mp4_write_box(p_ctx, MP4_BOX_TYPE_TRAK);
      if(status != VC_CONTAINER_SUCCESS) return status;
   }

   return status;
}