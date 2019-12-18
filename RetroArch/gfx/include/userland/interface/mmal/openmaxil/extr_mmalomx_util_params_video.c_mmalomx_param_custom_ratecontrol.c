#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  control; } ;
struct TYPE_8__ {TYPE_1__* format; } ;
struct TYPE_7__ {int /*<<< orphan*/  nTargetBitrate; int /*<<< orphan*/  eControlRate; } ;
struct TYPE_6__ {int /*<<< orphan*/  bitrate; } ;
typedef  TYPE_2__ OMX_VIDEO_PARAM_BITRATETYPE ;
typedef  scalar_t__ OMX_PTR ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_PORT_T ;
typedef  TYPE_4__ MMAL_PARAMETER_VIDEO_RATECONTROL_T ;
typedef  int /*<<< orphan*/  MMAL_PARAMETER_HEADER_T ;
typedef  int /*<<< orphan*/  MMALOMX_PARAM_TRANSLATION_T ;
typedef  scalar_t__ MMALOMX_PARAM_MAPPING_DIRECTION ;

/* Variables and functions */
 scalar_t__ MMALOMX_PARAM_MAPPING_TO_MMAL ; 
 int /*<<< orphan*/  MMAL_PARAM_UNUSED (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmalil_omx_video_ratecontrol_to_mmal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmalil_video_ratecontrol_to_omx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static MMAL_STATUS_T mmalomx_param_custom_ratecontrol(MMALOMX_PARAM_MAPPING_DIRECTION dir,
   const MMALOMX_PARAM_TRANSLATION_T *xlat,
   MMAL_PARAMETER_HEADER_T *mmal_param, OMX_PTR omx_param, MMAL_PORT_T *mmal_port)
{
   OMX_VIDEO_PARAM_BITRATETYPE *omx = (OMX_VIDEO_PARAM_BITRATETYPE *)omx_param;
   MMAL_PARAMETER_VIDEO_RATECONTROL_T *mmal = (MMAL_PARAMETER_VIDEO_RATECONTROL_T *)mmal_param;
   MMAL_PARAM_UNUSED(xlat);

   if (dir == MMALOMX_PARAM_MAPPING_TO_MMAL)
   {
      mmal->control = mmalil_omx_video_ratecontrol_to_mmal(omx->eControlRate);
      /* This does not apply nTargetBitrate but should not be necessary */
   }
   else
   {
      omx->eControlRate   = mmalil_video_ratecontrol_to_omx(mmal->control);
      omx->nTargetBitrate = mmal_port->format->bitrate; /* Should not really be necessary */
   }

   return MMAL_SUCCESS;
}