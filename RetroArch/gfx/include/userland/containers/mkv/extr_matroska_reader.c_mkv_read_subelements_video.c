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
struct TYPE_15__ {double frame_rate; void* aspect_ratio_type; void* display_unit; void* display_height; void* display_width; void* pixel_crop_right; void* pixel_crop_left; void* pixel_crop_top; void* pixel_crop_bottom; void* pixel_height; void* pixel_width; } ;
struct TYPE_16__ {TYPE_4__ video; } ;
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
#define  MKV_ELEMENT_ID_ASPECT_RATIO_TYPE 137 
#define  MKV_ELEMENT_ID_DISPLAY_HEIGHT 136 
#define  MKV_ELEMENT_ID_DISPLAY_UNIT 135 
#define  MKV_ELEMENT_ID_DISPLAY_WIDTH 134 
 int MKV_ELEMENT_ID_FRAME_RATE ; 
#define  MKV_ELEMENT_ID_PIXEL_CROP_BOTTOM 133 
#define  MKV_ELEMENT_ID_PIXEL_CROP_LEFT 132 
#define  MKV_ELEMENT_ID_PIXEL_CROP_RIGHT 131 
#define  MKV_ELEMENT_ID_PIXEL_CROP_TOP 130 
#define  MKV_ELEMENT_ID_PIXEL_HEIGHT 129 
#define  MKV_ELEMENT_ID_PIXEL_WIDTH 128 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ mkv_read_element_data_float (TYPE_7__*,int /*<<< orphan*/ ,double*) ; 
 scalar_t__ mkv_read_element_data_uint (TYPE_7__*,int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mkv_read_subelements_video( VC_CONTAINER_T *p_ctx, MKV_ELEMENT_ID_T id, int64_t size )
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_TRACK_MODULE_T *track_module = module->parsing->priv->module;
   uint64_t value;

   /* Deal with floating point values first */
   if(id == MKV_ELEMENT_ID_FRAME_RATE)
   {
      double fvalue;
      status = mkv_read_element_data_float(p_ctx, size, &fvalue);
      if(status != VC_CONTAINER_SUCCESS) return status;
      track_module->es_type.video.frame_rate = fvalue;
      return status;
   }

   /* The rest are just unsigned integers */
   status = mkv_read_element_data_uint(p_ctx, size, &value);
   if(status != VC_CONTAINER_SUCCESS) return status;

   switch(id)
   {
   case MKV_ELEMENT_ID_PIXEL_WIDTH: track_module->es_type.video.pixel_width = value; break;
   case MKV_ELEMENT_ID_PIXEL_HEIGHT: track_module->es_type.video.pixel_height = value; break;
   case MKV_ELEMENT_ID_PIXEL_CROP_BOTTOM: track_module->es_type.video.pixel_crop_bottom = value; break;
   case MKV_ELEMENT_ID_PIXEL_CROP_TOP: track_module->es_type.video.pixel_crop_top = value; break;
   case MKV_ELEMENT_ID_PIXEL_CROP_LEFT: track_module->es_type.video.pixel_crop_left = value; break;
   case MKV_ELEMENT_ID_PIXEL_CROP_RIGHT: track_module->es_type.video.pixel_crop_right = value; break;
   case MKV_ELEMENT_ID_DISPLAY_WIDTH: track_module->es_type.video.display_width = value; break;
   case MKV_ELEMENT_ID_DISPLAY_HEIGHT: track_module->es_type.video.display_height = value; break;
   case MKV_ELEMENT_ID_DISPLAY_UNIT: track_module->es_type.video.display_unit = value; break;
   case MKV_ELEMENT_ID_ASPECT_RATIO_TYPE: track_module->es_type.video.aspect_ratio_type = value; break;
   default: break;
   }

   return status;
}