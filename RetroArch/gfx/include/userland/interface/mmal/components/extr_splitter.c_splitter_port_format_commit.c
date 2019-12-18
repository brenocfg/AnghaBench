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
struct TYPE_7__ {unsigned int output_num; TYPE_1__** output; } ;
struct TYPE_6__ {scalar_t__ type; int /*<<< orphan*/  format; TYPE_3__* component; } ;
struct TYPE_5__ {int /*<<< orphan*/  format; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_PORT_T ;
typedef  TYPE_3__ MMAL_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 scalar_t__ MMAL_EINVAL ; 
 scalar_t__ MMAL_PORT_TYPE_OUTPUT ; 
 scalar_t__ MMAL_SUCCESS ; 
 scalar_t__ mmal_format_full_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static MMAL_STATUS_T splitter_port_format_commit(MMAL_PORT_T *port)
{
   MMAL_COMPONENT_T *component = port->component;
   MMAL_STATUS_T status;
   unsigned int i;

   /* Sanity check */
   if (port->type == MMAL_PORT_TYPE_OUTPUT)
   {
      LOG_ERROR("output port is read-only");
      return MMAL_EINVAL;
   }

   /* Commit the format on all output ports */
   for (i = 0; i < component->output_num; i++)
   {
      status = mmal_format_full_copy(component->output[i]->format, port->format);
      if (status != MMAL_SUCCESS)
         return status;
   }

   return MMAL_SUCCESS;
}