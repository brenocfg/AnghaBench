#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_13__ {unsigned int output_num; TYPE_4__* priv; TYPE_2__** output; TYPE_1__** input; } ;
struct TYPE_12__ {scalar_t__ type; int index; TYPE_6__* component; scalar_t__ buffer_size; } ;
struct TYPE_11__ {TYPE_3__* module; } ;
struct TYPE_10__ {int enabled_flags; } ;
struct TYPE_9__ {void* buffer_size; void* buffer_num; } ;
struct TYPE_8__ {void* buffer_size; void* buffer_num; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_5__ MMAL_PORT_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_BH_CB_T ;
typedef  TYPE_6__ MMAL_COMPONENT_T ;

/* Variables and functions */
 void* MMAL_MAX (void*,void*) ; 
 int /*<<< orphan*/  MMAL_PARAM_UNUSED (int /*<<< orphan*/ ) ; 
 scalar_t__ MMAL_PORT_TYPE_OUTPUT ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 

__attribute__((used)) static MMAL_STATUS_T splitter_port_enable(MMAL_PORT_T *port, MMAL_PORT_BH_CB_T cb)
{
#if 0
   MMAL_COMPONENT_T *component = port->component;
   uint32_t buffer_num, buffer_size;
   unsigned int i;

   /* Find the max and apply that to all ports */
   buffer_num = component->input[0]->buffer_num;
   buffer_size = component->input[0]->buffer_size;
   for (i = 0; i < component->output_num; i++)
   {
      buffer_num = MMAL_MAX(buffer_num, component->output[i]->buffer_num);
      buffer_size = MMAL_MAX(buffer_num, component->output[i]->buffer_size);
   }
   component->input[0]->buffer_num = buffer_num;
   component->input[0]->buffer_size = buffer_size;
   for (i = 0; i < component->output_num; i++)
   {
      component->output[i]->buffer_num = buffer_num;
      component->output[i]->buffer_size = buffer_num;
   }
#endif

   MMAL_PARAM_UNUSED(cb);
   if (port->buffer_size)
   if (port->type == MMAL_PORT_TYPE_OUTPUT)
      port->component->priv->module->enabled_flags |= (1<<port->index);
   return MMAL_SUCCESS;
}