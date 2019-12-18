#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stereo ;
struct TYPE_4__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {scalar_t__ member_1; scalar_t__ mode; int /*<<< orphan*/  hdr; int /*<<< orphan*/  swap_eyes; int /*<<< orphan*/  decimate; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; TYPE_1__ member_0; } ;
typedef  int /*<<< orphan*/  MMAL_PORT_T ;
typedef  TYPE_2__ MMAL_PARAMETER_STEREOSCOPIC_MODE_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_FALSE ; 
 int /*<<< orphan*/  MMAL_PARAMETER_STEREOSCOPIC_MODE ; 
 scalar_t__ MMAL_STEREOSCOPIC_MODE_NONE ; 
 int /*<<< orphan*/  mmal_port_parameter_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mmal_status_to_int (int /*<<< orphan*/ ) ; 

int raspicamcontrol_set_stereo_mode(MMAL_PORT_T *port, MMAL_PARAMETER_STEREOSCOPIC_MODE_T *stereo_mode)
{
   MMAL_PARAMETER_STEREOSCOPIC_MODE_T stereo = { {MMAL_PARAMETER_STEREOSCOPIC_MODE, sizeof(stereo)},
      MMAL_STEREOSCOPIC_MODE_NONE, MMAL_FALSE, MMAL_FALSE
   };
   if (stereo_mode->mode != MMAL_STEREOSCOPIC_MODE_NONE)
   {
      stereo.mode = stereo_mode->mode;
      stereo.decimate = stereo_mode->decimate;
      stereo.swap_eyes = stereo_mode->swap_eyes;
   }
   return mmal_status_to_int(mmal_port_parameter_set(port, &stereo.hdr));
}