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
struct TYPE_7__ {scalar_t__ type; size_t index; int /*<<< orphan*/  format; TYPE_2__* component; } ;
struct TYPE_6__ {TYPE_1__** output; } ;
struct TYPE_5__ {int /*<<< orphan*/  format; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 int /*<<< orphan*/  MMAL_EINVAL ; 
 scalar_t__ MMAL_PORT_TYPE_OUTPUT ; 
 int /*<<< orphan*/  mmal_format_full_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static MMAL_STATUS_T passthrough_port_format_commit(MMAL_PORT_T *port)
{
   /* Sanity check */
   if (port->type == MMAL_PORT_TYPE_OUTPUT)
   {
      LOG_ERROR("output port is read-only");
      return MMAL_EINVAL;
   }

   return mmal_format_full_copy(port->component->output[port->index]->format, port->format);
}