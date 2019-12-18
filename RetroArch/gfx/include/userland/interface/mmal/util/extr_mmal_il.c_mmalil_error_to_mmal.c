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
typedef  scalar_t__ OMX_ERRORTYPE ;
typedef  scalar_t__ MMAL_STATUS_T ;

/* Variables and functions */
 TYPE_1__* mmal_omx_error ; 

MMAL_STATUS_T mmalil_error_to_mmal(OMX_ERRORTYPE error)
{
   unsigned int i;
   for(i = 0; mmal_omx_error[i].mmal != (MMAL_STATUS_T)-1; i++)
      if(mmal_omx_error[i].omx == error) break;
   return mmal_omx_error[i].mmal;
}