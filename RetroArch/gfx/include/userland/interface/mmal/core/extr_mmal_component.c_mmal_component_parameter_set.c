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
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_T ;
typedef  TYPE_1__ MMAL_PARAMETER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMAL_ENOSYS ; 

MMAL_STATUS_T mmal_component_parameter_set(MMAL_PORT_T *control_port,
                                           const MMAL_PARAMETER_HEADER_T *param)
{
   (void)control_port;
   (void)param;
   /* No generic component control parameters */
   LOG_ERROR("parameter id 0x%08x not supported", param->id);
   return MMAL_ENOSYS;
}