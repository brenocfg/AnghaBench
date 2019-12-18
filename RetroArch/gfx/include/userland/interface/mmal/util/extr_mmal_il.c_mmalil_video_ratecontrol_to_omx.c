#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ mmal; int /*<<< orphan*/  omx; } ;
typedef  int /*<<< orphan*/  OMX_VIDEO_CONTROLRATETYPE ;
typedef  scalar_t__ MMAL_VIDEO_RATECONTROL_T ;

/* Variables and functions */
 scalar_t__ MMAL_VIDEO_RATECONTROL_DUMMY ; 
 TYPE_1__* mmal_omx_video_ratecontrol_table ; 

OMX_VIDEO_CONTROLRATETYPE mmalil_video_ratecontrol_to_omx(MMAL_VIDEO_RATECONTROL_T mmal)
{
   unsigned int i;
   for(i = 0; mmal_omx_video_ratecontrol_table[i].mmal != MMAL_VIDEO_RATECONTROL_DUMMY; i++)
      if(mmal_omx_video_ratecontrol_table[i].mmal == mmal) break;
   return mmal_omx_video_ratecontrol_table[i].omx;
}