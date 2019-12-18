#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int id; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_T ;
typedef  TYPE_1__ MMAL_PARAMETER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_ENOSYS ; 
#define  MMAL_PARAMETER_CORE_STATISTICS 128 
 int /*<<< orphan*/  mmal_port_get_core_stats (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_port_private_parameter_get(MMAL_PORT_T *port,
                                                     MMAL_PARAMETER_HEADER_T *param)
{
   switch (param->id)
   {
   case MMAL_PARAMETER_CORE_STATISTICS:
      return mmal_port_get_core_stats(port, param);
   default:
      return MMAL_ENOSYS;
   }
}