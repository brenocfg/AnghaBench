#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  revision; int /*<<< orphan*/  manufacturer_id; int /*<<< orphan*/  model_id; void* focal_length; void* f_number; } ;
struct TYPE_3__ {int /*<<< orphan*/  nRevNum; int /*<<< orphan*/  nManufacturerId; int /*<<< orphan*/  nModelId; void* xFocalLength; void* xFNumber; } ;
typedef  scalar_t__ OMX_PTR ;
typedef  TYPE_1__ OMX_CONFIG_CAMERAINFOTYPE ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_PARAMETER_SENSOR_INFORMATION_T ;
typedef  int /*<<< orphan*/  MMAL_PARAMETER_HEADER_T ;
typedef  scalar_t__ MMALOMX_PARAM_MAPPING_DIRECTION ;

/* Variables and functions */
 scalar_t__ MMALOMX_PARAM_MAPPING_TO_MMAL ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 void* mmal_rational_from_fixed_16_16 (void*) ; 
 void* mmal_rational_to_fixed_16_16 (void*) ; 

__attribute__((used)) static MMAL_STATUS_T mmalomx_param_mapping_sensor_info(MMALOMX_PARAM_MAPPING_DIRECTION dir,
   MMAL_PARAMETER_HEADER_T *mmal_param, OMX_PTR omx_param)
{
   OMX_CONFIG_CAMERAINFOTYPE *omx = (OMX_CONFIG_CAMERAINFOTYPE *)omx_param;
   MMAL_PARAMETER_SENSOR_INFORMATION_T *mmal = (MMAL_PARAMETER_SENSOR_INFORMATION_T *)mmal_param;

   if (dir == MMALOMX_PARAM_MAPPING_TO_MMAL)
   {
      mmal->f_number = mmal_rational_from_fixed_16_16(omx->xFNumber);
      mmal->focal_length = mmal_rational_from_fixed_16_16(omx->xFocalLength);
      mmal->model_id = omx->nModelId;
      mmal->manufacturer_id = omx->nManufacturerId;
      mmal->revision = omx->nRevNum;
   }
   else
   {
      omx->xFNumber = mmal_rational_to_fixed_16_16(mmal->f_number);
      omx->xFocalLength = mmal_rational_to_fixed_16_16(mmal->focal_length);
      omx->nModelId = mmal->model_id;
      omx->nManufacturerId = mmal->manufacturer_id;
      omx->nRevNum = mmal->revision;
   }

   return MMAL_SUCCESS;
}