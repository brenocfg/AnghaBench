#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int size; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {TYPE_3__ hdr; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_T ;
typedef  TYPE_1__ MMAL_DISPLAYREGION_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_PARAMETER_DISPLAYREGION ; 
 int /*<<< orphan*/  mmal_port_parameter_set (int /*<<< orphan*/ *,TYPE_3__*) ; 

MMAL_STATUS_T mmal_util_set_display_region(MMAL_PORT_T *port,
                                           MMAL_DISPLAYREGION_T *region)
{
   region->hdr.id = MMAL_PARAMETER_DISPLAYREGION;
   region->hdr.size = sizeof(*region);
   return mmal_port_parameter_set(port, &region->hdr);
}