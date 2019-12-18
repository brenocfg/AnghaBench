#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  control; } ;
struct TYPE_5__ {int member_0; int member_1; } ;
typedef  TYPE_1__ MMAL_RATIONAL_T ;
typedef  TYPE_2__ MMAL_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_PARAMETER_CONTRAST ; 
 int /*<<< orphan*/  mmal_port_parameter_set_rational (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__) ; 
 int mmal_status_to_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_error (char*) ; 

int raspicamcontrol_set_contrast(MMAL_COMPONENT_T *camera, int contrast)
{
   int ret = 0;

   if (!camera)
      return 1;

   if (contrast >= -100 && contrast <= 100)
   {
      MMAL_RATIONAL_T value = {contrast, 100};
      ret = mmal_status_to_int(mmal_port_parameter_set_rational(camera->control, MMAL_PARAMETER_CONTRAST, value));
   }
   else
   {
      vcos_log_error("Invalid contrast value");
      ret = 1;
   }

   return ret;
}