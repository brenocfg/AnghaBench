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
struct TYPE_2__ {scalar_t__ mmal; scalar_t__ omx; } ;
typedef  scalar_t__ OMX_VIDEO_INTRAREFRESHTYPE ;
typedef  scalar_t__ MMAL_VIDEO_INTRA_REFRESH_T ;

/* Variables and functions */
 scalar_t__ MMAL_VIDEO_INTRA_REFRESH_DUMMY ; 
 TYPE_1__* mmal_omx_video_intrarefresh_table ; 

MMAL_VIDEO_INTRA_REFRESH_T mmalil_omx_video_intrarefresh_to_mmal(OMX_VIDEO_INTRAREFRESHTYPE omx)
{
   unsigned int i;
   for(i = 0; mmal_omx_video_intrarefresh_table[i].mmal != MMAL_VIDEO_INTRA_REFRESH_DUMMY; i++)
      if(mmal_omx_video_intrarefresh_table[i].omx == omx) break;
   return mmal_omx_video_intrarefresh_table[i].mmal;
}