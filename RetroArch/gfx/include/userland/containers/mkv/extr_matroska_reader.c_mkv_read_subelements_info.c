#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_9__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_10__ {double duration; int /*<<< orphan*/  timecode_scale; } ;
typedef  TYPE_3__ VC_CONTAINER_MODULE_T ;
struct TYPE_8__ {TYPE_3__* module; } ;
typedef  int MKV_ELEMENT_ID_T ;

/* Variables and functions */
#define  MKV_ELEMENT_ID_DURATION 132 
#define  MKV_ELEMENT_ID_MUXING_APP 131 
#define  MKV_ELEMENT_ID_TIMECODE_SCALE 130 
#define  MKV_ELEMENT_ID_TITLE 129 
#define  MKV_ELEMENT_ID_WRITING_APP 128 
 int /*<<< orphan*/  SKIP_STRING (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  mkv_read_element_data_float (TYPE_2__*,int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  mkv_read_element_data_uint (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mkv_read_subelements_info( VC_CONTAINER_T *p_ctx, MKV_ELEMENT_ID_T id, int64_t size )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   uint64_t value;
   double fvalue;

   switch(id)
   {
   case MKV_ELEMENT_ID_TIMECODE_SCALE:
      status = mkv_read_element_data_uint(p_ctx, size, &value);
      if(status != VC_CONTAINER_SUCCESS) break;
      module->timecode_scale = value;
      break;
   case MKV_ELEMENT_ID_DURATION:
      status = mkv_read_element_data_float(p_ctx, size, &fvalue);
      if(status != VC_CONTAINER_SUCCESS) break;
      module->duration = fvalue;
      break;
   case MKV_ELEMENT_ID_TITLE:
   case MKV_ELEMENT_ID_MUXING_APP:
   case MKV_ELEMENT_ID_WRITING_APP:
      SKIP_STRING(p_ctx, size, "string");
      break;

   default: break;
   }

   return status;
}