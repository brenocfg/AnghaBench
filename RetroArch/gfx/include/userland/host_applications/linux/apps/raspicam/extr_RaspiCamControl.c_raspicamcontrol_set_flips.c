#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * output; } ;
struct TYPE_5__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int /*<<< orphan*/  hdr; int /*<<< orphan*/  value; int /*<<< orphan*/  member_1; TYPE_1__ member_0; } ;
typedef  TYPE_2__ MMAL_PARAMETER_MIRROR_T ;
typedef  TYPE_3__ MMAL_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_PARAMETER_MIRROR ; 
 int /*<<< orphan*/  MMAL_PARAM_MIRROR_BOTH ; 
 int /*<<< orphan*/  MMAL_PARAM_MIRROR_HORIZONTAL ; 
 int /*<<< orphan*/  MMAL_PARAM_MIRROR_NONE ; 
 int /*<<< orphan*/  MMAL_PARAM_MIRROR_VERTICAL ; 
 int /*<<< orphan*/  mmal_port_parameter_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mmal_status_to_int (int /*<<< orphan*/ ) ; 

int raspicamcontrol_set_flips(MMAL_COMPONENT_T *camera, int hflip, int vflip)
{
   MMAL_PARAMETER_MIRROR_T mirror = {{MMAL_PARAMETER_MIRROR, sizeof(MMAL_PARAMETER_MIRROR_T)}, MMAL_PARAM_MIRROR_NONE};

   if (hflip && vflip)
      mirror.value = MMAL_PARAM_MIRROR_BOTH;
   else if (hflip)
      mirror.value = MMAL_PARAM_MIRROR_HORIZONTAL;
   else if (vflip)
      mirror.value = MMAL_PARAM_MIRROR_VERTICAL;

   mmal_port_parameter_set(camera->output[0], &mirror.hdr);
   mmal_port_parameter_set(camera->output[1], &mirror.hdr);
   return mmal_status_to_int(mmal_port_parameter_set(camera->output[2], &mirror.hdr));
}