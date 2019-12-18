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
struct TYPE_7__ {scalar_t__ tracks_num; TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_8__ {scalar_t__ current_track; } ;
typedef  TYPE_3__ VC_CONTAINER_MODULE_T ;
struct TYPE_6__ {TYPE_3__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASF_OBJECT_TYPE_EXT_STREAM_PROPS ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  asf_write_object (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T asf_write_object_header_ext_internal( VC_CONTAINER_T *p_ctx )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;

   for(module->current_track = 0; module->current_track < p_ctx->tracks_num;
       module->current_track++)
   {
      status = asf_write_object(p_ctx, ASF_OBJECT_TYPE_EXT_STREAM_PROPS);
   }

   return status;
}