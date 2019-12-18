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
typedef  void* uint64_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_7__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_8__ {void* cue_block; void* cue_cluster_offset; void* cue_track; void* cue_timecode; } ;
typedef  TYPE_3__ VC_CONTAINER_MODULE_T ;
struct TYPE_6__ {TYPE_3__* module; } ;
typedef  int MKV_ELEMENT_ID_T ;

/* Variables and functions */
#define  MKV_ELEMENT_ID_CUE_BLOCK_NUMBER 131 
#define  MKV_ELEMENT_ID_CUE_CLUSTER_POSITION 130 
#define  MKV_ELEMENT_ID_CUE_TIME 129 
#define  MKV_ELEMENT_ID_CUE_TRACK 128 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ mkv_read_element_data_uint (TYPE_2__*,int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mkv_read_subelements_cue_point( VC_CONTAINER_T *p_ctx, MKV_ELEMENT_ID_T id, int64_t size )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_STATUS_T status;
   uint64_t value;

   /* All the values are unsigned integers */
   status = mkv_read_element_data_uint(p_ctx, size, &value);
   if(status != VC_CONTAINER_SUCCESS) return status;

   switch(id)
   {
   case MKV_ELEMENT_ID_CUE_TIME:
      module->cue_timecode = value; break;
   case MKV_ELEMENT_ID_CUE_TRACK:
      module->cue_track = value; break;
   case MKV_ELEMENT_ID_CUE_CLUSTER_POSITION:
      module->cue_cluster_offset = value; break;
   case MKV_ELEMENT_ID_CUE_BLOCK_NUMBER:
      module->cue_block = value; break;
   default: break;
   }

   return status;
}