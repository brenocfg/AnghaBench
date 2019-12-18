#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* profile; } ;
struct TYPE_10__ {TYPE_1__* format; } ;
struct TYPE_9__ {int /*<<< orphan*/  eLevel; int /*<<< orphan*/  eProfile; } ;
struct TYPE_8__ {int /*<<< orphan*/  level; int /*<<< orphan*/  profile; } ;
struct TYPE_7__ {int /*<<< orphan*/  encoding; } ;
typedef  TYPE_3__ OMX_VIDEO_PARAM_PROFILELEVELTYPE ;
typedef  int /*<<< orphan*/  OMX_VIDEO_CODINGTYPE ;
typedef  scalar_t__ OMX_PTR ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_4__ MMAL_PORT_T ;
typedef  TYPE_5__ MMAL_PARAMETER_VIDEO_PROFILE_T ;
typedef  int /*<<< orphan*/  MMAL_PARAMETER_HEADER_T ;
typedef  int /*<<< orphan*/  MMALOMX_PARAM_TRANSLATION_T ;
typedef  scalar_t__ MMALOMX_PARAM_MAPPING_DIRECTION ;

/* Variables and functions */
 scalar_t__ MMALOMX_PARAM_MAPPING_TO_MMAL ; 
 int /*<<< orphan*/  MMAL_PARAM_UNUSED (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmalil_encoding_to_omx_video_coding (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmalil_omx_video_level_to_mmal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmalil_omx_video_profile_to_mmal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmalil_video_level_to_omx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmalil_video_profile_to_omx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static MMAL_STATUS_T mmalomx_param_custom_profile(MMALOMX_PARAM_MAPPING_DIRECTION dir,
   const MMALOMX_PARAM_TRANSLATION_T *xlat,
   MMAL_PARAMETER_HEADER_T *mmal_param, OMX_PTR omx_param, MMAL_PORT_T *mmal_port)
{
   OMX_VIDEO_PARAM_PROFILELEVELTYPE *omx = (OMX_VIDEO_PARAM_PROFILELEVELTYPE *)omx_param;
   MMAL_PARAMETER_VIDEO_PROFILE_T *mmal = (MMAL_PARAMETER_VIDEO_PROFILE_T *)mmal_param;
   MMAL_PARAM_UNUSED(xlat);

   if (dir == MMALOMX_PARAM_MAPPING_TO_MMAL)
   {
      OMX_VIDEO_CODINGTYPE coding = mmalil_encoding_to_omx_video_coding(mmal_port->format->encoding);
      mmal->profile[0].profile = mmalil_omx_video_profile_to_mmal(omx->eProfile, coding);
      mmal->profile[0].level = mmalil_omx_video_level_to_mmal(omx->eLevel, coding);
   }
   else
   {
      omx->eProfile = mmalil_video_profile_to_omx(mmal->profile[0].profile);
      omx->eLevel = mmalil_video_level_to_omx(mmal->profile[0].level);
   }

   return MMAL_SUCCESS;
}