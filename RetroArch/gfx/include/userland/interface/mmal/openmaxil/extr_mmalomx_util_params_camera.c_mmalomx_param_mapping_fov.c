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
struct TYPE_4__ {void* fov_v; void* fov_h; } ;
struct TYPE_3__ {void* xFieldOfViewVertical; void* xFieldOfViewHorizontal; } ;
typedef  scalar_t__ OMX_PTR ;
typedef  TYPE_1__ OMX_CONFIG_BRCMFOVTYPE ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_PARAMETER_HEADER_T ;
typedef  TYPE_2__ MMAL_PARAMETER_FIELD_OF_VIEW_T ;
typedef  scalar_t__ MMALOMX_PARAM_MAPPING_DIRECTION ;

/* Variables and functions */
 scalar_t__ MMALOMX_PARAM_MAPPING_TO_MMAL ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 void* mmal_rational_from_fixed_16_16 (void*) ; 
 void* mmal_rational_to_fixed_16_16 (void*) ; 

__attribute__((used)) static MMAL_STATUS_T mmalomx_param_mapping_fov(MMALOMX_PARAM_MAPPING_DIRECTION dir,
   MMAL_PARAMETER_HEADER_T *mmal_param, OMX_PTR omx_param)
{
   OMX_CONFIG_BRCMFOVTYPE *omx = (OMX_CONFIG_BRCMFOVTYPE *)omx_param;
   MMAL_PARAMETER_FIELD_OF_VIEW_T *mmal = (MMAL_PARAMETER_FIELD_OF_VIEW_T *)mmal_param;

   if (dir == MMALOMX_PARAM_MAPPING_TO_MMAL)
   {
      mmal->fov_h = mmal_rational_from_fixed_16_16(omx->xFieldOfViewHorizontal);
      mmal->fov_v = mmal_rational_from_fixed_16_16(omx->xFieldOfViewVertical);
   }
   else
   {
      omx->xFieldOfViewHorizontal = mmal_rational_to_fixed_16_16(mmal->fov_h);
      omx->xFieldOfViewVertical = mmal_rational_to_fixed_16_16(mmal->fov_v);
   }

   return MMAL_SUCCESS;
}