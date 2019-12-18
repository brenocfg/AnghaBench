#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  mmal_param ;
struct TYPE_18__ {TYPE_3__* format; } ;
struct TYPE_17__ {TYPE_9__* mmal; } ;
struct TYPE_12__ {scalar_t__ member_1; scalar_t__ member_0; } ;
struct TYPE_11__ {TYPE_2__ member_0; } ;
struct TYPE_15__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_16__ {int /*<<< orphan*/  hdr; TYPE_4__* profile; TYPE_1__ member_1; TYPE_5__ member_0; } ;
struct TYPE_14__ {scalar_t__ level; scalar_t__ profile; } ;
struct TYPE_13__ {int /*<<< orphan*/  encoding; } ;
typedef  int /*<<< orphan*/  OMX_VIDEO_CODINGTYPE ;
typedef  int /*<<< orphan*/  OMX_ERRORTYPE ;
typedef  scalar_t__ MMAL_VIDEO_PROFILE_T ;
typedef  scalar_t__ MMAL_VIDEO_LEVEL_T ;
typedef  TYPE_6__ MMAL_PARAMETER_VIDEO_PROFILE_T ;
typedef  TYPE_7__ MMALOMX_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_PARAMETER_INTRAPERIOD ; 
 int /*<<< orphan*/  MMAL_PARAMETER_PROFILE ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  OMX_ErrorBadParameter ; 
 int /*<<< orphan*/  OMX_ErrorNone ; 
 scalar_t__ mmal_port_parameter_set (TYPE_9__*,int /*<<< orphan*/ *) ; 
 scalar_t__ mmal_port_parameter_set_uint32 (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmalil_encoding_to_omx_video_coding (int /*<<< orphan*/ ) ; 
 scalar_t__ mmalil_omx_video_level_to_mmal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mmalil_omx_video_profile_to_mmal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static OMX_ERRORTYPE mmalomx_set_video_param(MMALOMX_PORT_T *port,
   uint32_t profile, uint32_t level, uint32_t intraperiod)
{
   MMAL_PARAMETER_VIDEO_PROFILE_T mmal_param = {{MMAL_PARAMETER_PROFILE, sizeof(mmal_param)},
      {{(MMAL_VIDEO_PROFILE_T)0, (MMAL_VIDEO_LEVEL_T)0}}};
   OMX_VIDEO_CODINGTYPE coding =
      mmalil_encoding_to_omx_video_coding(port->mmal->format->encoding);

   if (mmal_port_parameter_set_uint32(port->mmal, MMAL_PARAMETER_INTRAPERIOD,
          intraperiod) != MMAL_SUCCESS)
      return OMX_ErrorBadParameter;

   mmal_param.profile[0].profile = (MMAL_VIDEO_PROFILE_T)
      mmalil_omx_video_profile_to_mmal(profile, coding);
   mmal_param.profile[0].level = (MMAL_VIDEO_LEVEL_T)
      mmalil_omx_video_level_to_mmal(level, coding);
   if (mmal_port_parameter_set(port->mmal, &mmal_param.hdr) != MMAL_SUCCESS)
      return OMX_ErrorBadParameter;

   return OMX_ErrorNone;
}