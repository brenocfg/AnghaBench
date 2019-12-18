#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {scalar_t__ length; } ;
struct TYPE_22__ {int error; int sent_flags; int enabled_flags; } ;
struct TYPE_21__ {unsigned int output_num; TYPE_4__** output; TYPE_4__** input; TYPE_1__* priv; } ;
struct TYPE_20__ {TYPE_5__* component; TYPE_3__* priv; } ;
struct TYPE_19__ {TYPE_2__* module; } ;
struct TYPE_18__ {int /*<<< orphan*/  queue; } ;
struct TYPE_17__ {TYPE_6__* module; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_4__ MMAL_PORT_T ;
typedef  TYPE_5__ MMAL_COMPONENT_T ;
typedef  TYPE_6__ MMAL_COMPONENT_MODULE_T ;
typedef  TYPE_7__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,int) ; 
 scalar_t__ MMAL_EAGAIN ; 
 scalar_t__ MMAL_SUCCESS ; 
 scalar_t__ mmal_event_error_send (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  mmal_port_buffer_header_callback (TYPE_4__*,TYPE_7__*) ; 
 TYPE_7__* mmal_queue_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_queue_put (int /*<<< orphan*/ ,TYPE_7__*) ; 
 scalar_t__ splitter_send_output (TYPE_7__*,TYPE_4__*) ; 

__attribute__((used)) static MMAL_STATUS_T splitter_port_send(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
   MMAL_COMPONENT_T *component = port->component;
   MMAL_COMPONENT_MODULE_T *module = component->priv->module;
   MMAL_PORT_T *in_port, *out_port;
   MMAL_BUFFER_HEADER_T *in;
   MMAL_STATUS_T status;
   unsigned int i;

   mmal_queue_put(port->priv->module->queue, buffer);

   if (module->error)
      return MMAL_SUCCESS; /* Just do nothing */

   /* Get input buffer header */
   in_port = component->input[0];
   in = mmal_queue_get(in_port->priv->module->queue);
   if (!in)
      return MMAL_SUCCESS; /* Nothing to do */

   for (i = 0; i < component->output_num; i++)
   {
      out_port = component->output[i];
      status = splitter_send_output(in, out_port);

      if (status != MMAL_SUCCESS && status != MMAL_EAGAIN)
         goto error;

      if (status == MMAL_SUCCESS)
         module->sent_flags |= (1<<i);
   }

   /* Check if we're done with the input buffer */
   if ((module->sent_flags & module->enabled_flags) == module->enabled_flags)
   {
      in->length = 0; /* Consume the input buffer */
      mmal_port_buffer_header_callback(in_port, in);
      module->sent_flags = 0;
      return MMAL_SUCCESS;
   }

   /* We're not done yet so put the buffer back in the queue */
   mmal_queue_put(in_port->priv->module->queue, in);
   return MMAL_SUCCESS;

 error:
   mmal_queue_put(in_port->priv->module->queue, in);

   status = mmal_event_error_send(port->component, status);
   if (status != MMAL_SUCCESS)
   {
      LOG_ERROR("unable to send an error event buffer (%i)", (int)status);
      return MMAL_SUCCESS;
   }
   module->error = 1;
   return MMAL_SUCCESS;
}