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
typedef  void* uint64_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_9__ {TYPE_1__* priv; } ;
typedef  TYPE_3__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_8__ {void* frame_duration; void* cluster_timecode; } ;
struct TYPE_10__ {TYPE_2__ state; } ;
typedef  TYPE_4__ VC_CONTAINER_MODULE_T ;
struct TYPE_7__ {TYPE_4__* module; } ;
typedef  int MKV_ELEMENT_ID_T ;

/* Variables and functions */
#define  MKV_ELEMENT_ID_BLOCK_DURATION 129 
#define  MKV_ELEMENT_ID_TIMECODE 128 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ mkv_read_element_data_uint (TYPE_3__*,int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mkv_read_subelements_cluster( VC_CONTAINER_T *p_ctx, MKV_ELEMENT_ID_T id, int64_t size )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_STATUS_T status;
   uint64_t value;

   /* The rest are just unsigned integers */
   status = mkv_read_element_data_uint(p_ctx, size, &value);
   if(status != VC_CONTAINER_SUCCESS) return status;

   switch(id)
   {
   //XXX
   case MKV_ELEMENT_ID_TIMECODE: module->state.cluster_timecode = value; break;
   case MKV_ELEMENT_ID_BLOCK_DURATION: module->state.frame_duration = value; break;
   default: break;
   }

   return status;
}