#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  control; } ;
typedef  TYPE_1__ MMAL_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_PARAMETER_CAPTURE_STATS_PASS ; 
 int /*<<< orphan*/  mmal_port_parameter_set_boolean (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mmal_status_to_int (int /*<<< orphan*/ ) ; 

int raspicamcontrol_set_stats_pass(MMAL_COMPONENT_T *camera, int stats_pass)
{
   if (!camera)
      return 1;

   return mmal_status_to_int(mmal_port_parameter_set_boolean(camera->control, MMAL_PARAMETER_CAPTURE_STATS_PASS, stats_pass));
}