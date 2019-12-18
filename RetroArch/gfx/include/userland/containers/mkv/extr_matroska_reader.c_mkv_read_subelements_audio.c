#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_15__ {double sampling_frequency; double output_sampling_frequency; void* bit_depth; void* channels; } ;
struct TYPE_16__ {TYPE_4__ audio; } ;
struct TYPE_17__ {TYPE_5__ es_type; } ;
typedef  TYPE_6__ VC_CONTAINER_TRACK_MODULE_T ;
struct TYPE_18__ {TYPE_1__* priv; } ;
typedef  TYPE_7__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_19__ {TYPE_3__* parsing; } ;
typedef  TYPE_8__ VC_CONTAINER_MODULE_T ;
struct TYPE_14__ {TYPE_2__* priv; } ;
struct TYPE_13__ {TYPE_6__* module; } ;
struct TYPE_12__ {TYPE_8__* module; } ;
typedef  int MKV_ELEMENT_ID_T ;

/* Variables and functions */
#define  MKV_ELEMENT_ID_BIT_DEPTH 129 
#define  MKV_ELEMENT_ID_CHANNELS 128 
 int MKV_ELEMENT_ID_OUTPUT_SAMPLING_FREQUENCY ; 
 int MKV_ELEMENT_ID_SAMPLING_FREQUENCY ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ mkv_read_element_data_float (TYPE_7__*,int /*<<< orphan*/ ,double*) ; 
 scalar_t__ mkv_read_element_data_uint (TYPE_7__*,int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mkv_read_subelements_audio( VC_CONTAINER_T *p_ctx, MKV_ELEMENT_ID_T id, int64_t size )
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_TRACK_MODULE_T *track_module = module->parsing->priv->module;
   uint64_t value;

   /* Deal with floating point values first */
   if(id == MKV_ELEMENT_ID_SAMPLING_FREQUENCY ||
      id == MKV_ELEMENT_ID_OUTPUT_SAMPLING_FREQUENCY)
   {
      double fvalue;
      status = mkv_read_element_data_float(p_ctx, size, &fvalue);
      if(status != VC_CONTAINER_SUCCESS) return status;

      if(id == MKV_ELEMENT_ID_SAMPLING_FREQUENCY)
         track_module->es_type.audio.sampling_frequency = fvalue;

      if(id == MKV_ELEMENT_ID_OUTPUT_SAMPLING_FREQUENCY)
         track_module->es_type.audio.output_sampling_frequency = fvalue;

      return status;
   }

   /* The rest are just unsigned integers */
   status = mkv_read_element_data_uint(p_ctx, size, &value);
   if(status != VC_CONTAINER_SUCCESS) return status;

   switch(id)
   {
   case MKV_ELEMENT_ID_CHANNELS: track_module->es_type.audio.channels = value; break;
   case MKV_ELEMENT_ID_BIT_DEPTH: track_module->es_type.audio.bit_depth = value; break;
   default: break;
   }

   return status;
}