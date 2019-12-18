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
typedef  int /*<<< orphan*/  imgFX ;
struct TYPE_7__ {int /*<<< orphan*/  control; } ;
struct TYPE_5__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int /*<<< orphan*/  hdr; int /*<<< orphan*/  member_1; TYPE_1__ member_0; } ;
typedef  int /*<<< orphan*/  MMAL_PARAM_IMAGEFX_T ;
typedef  TYPE_2__ MMAL_PARAMETER_IMAGEFX_T ;
typedef  TYPE_3__ MMAL_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_PARAMETER_IMAGE_EFFECT ; 
 int /*<<< orphan*/  mmal_port_parameter_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mmal_status_to_int (int /*<<< orphan*/ ) ; 

int raspicamcontrol_set_imageFX(MMAL_COMPONENT_T *camera, MMAL_PARAM_IMAGEFX_T imageFX)
{
   MMAL_PARAMETER_IMAGEFX_T imgFX = {{MMAL_PARAMETER_IMAGE_EFFECT,sizeof(imgFX)}, imageFX};

   if (!camera)
      return 1;

   return mmal_status_to_int(mmal_port_parameter_set(camera->control, &imgFX.hdr));
}