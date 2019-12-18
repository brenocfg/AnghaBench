#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_4__ {int num; int den; } ;
struct TYPE_6__ {TYPE_1__ frame_rate; } ;
struct TYPE_5__ {int xEncodeFramerate; } ;
typedef  scalar_t__ OMX_PTR ;
typedef  TYPE_2__ OMX_CONFIG_FRAMERATETYPE ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_PARAMETER_HEADER_T ;
typedef  TYPE_3__ MMAL_PARAMETER_FRAME_RATE_T ;
typedef  scalar_t__ MMALOMX_PARAM_MAPPING_DIRECTION ;

/* Variables and functions */
 scalar_t__ MMALOMX_PARAM_MAPPING_TO_MMAL ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 

__attribute__((used)) static MMAL_STATUS_T mmalomx_param_mapping_frame_rate(MMALOMX_PARAM_MAPPING_DIRECTION dir,
   MMAL_PARAMETER_HEADER_T *mmal_param, OMX_PTR omx_param)
{
   OMX_CONFIG_FRAMERATETYPE *omx = (OMX_CONFIG_FRAMERATETYPE *)omx_param;
   MMAL_PARAMETER_FRAME_RATE_T *mmal = (MMAL_PARAMETER_FRAME_RATE_T *)mmal_param;

   if (dir == MMALOMX_PARAM_MAPPING_TO_MMAL)
   {
      mmal->frame_rate.num = omx->xEncodeFramerate;
      mmal->frame_rate.den = (1<<16);
   }
   else
   {
      omx->xEncodeFramerate = 0;
      if (mmal->frame_rate.den)
         omx->xEncodeFramerate = (((int64_t)mmal->frame_rate.num)<<16)/mmal->frame_rate.den;
   }

   return MMAL_SUCCESS;
}