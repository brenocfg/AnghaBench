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
struct TYPE_7__ {size_t index; TYPE_2__* component; int /*<<< orphan*/  format; } ;
struct TYPE_6__ {TYPE_1__** input; } ;
struct TYPE_5__ {int /*<<< orphan*/  format; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (char*) ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 scalar_t__ mmal_format_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static MMAL_STATUS_T scheduler_output_port_format_commit(MMAL_PORT_T *port)
{
   /* The format of the output port needs to match the input port */
   if (mmal_format_compare(port->format, port->component->input[port->index]->format))
      LOG_DEBUG("output port format different from input port");

   return MMAL_SUCCESS;
}