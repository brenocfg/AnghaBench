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
struct TYPE_22__ {int error; } ;
struct TYPE_21__ {TYPE_4__** output; TYPE_4__** input; TYPE_1__* priv; } ;
struct TYPE_20__ {size_t index; scalar_t__ type; TYPE_5__* component; TYPE_3__* priv; } ;
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
 scalar_t__ MMAL_PORT_TYPE_INPUT ; 
 scalar_t__ MMAL_SUCCESS ; 
 scalar_t__ mmal_buffer_header_replicate (TYPE_7__*,TYPE_7__*) ; 
 scalar_t__ mmal_event_error_send (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  mmal_port_buffer_header_callback (TYPE_4__*,TYPE_7__*) ; 
 TYPE_7__* mmal_queue_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_queue_put (int /*<<< orphan*/ ,TYPE_7__*) ; 

__attribute__((used)) static MMAL_STATUS_T passthrough_port_send(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
   MMAL_COMPONENT_T *component = port->component;
   MMAL_COMPONENT_MODULE_T *module = component->priv->module;
   MMAL_PORT_T **other_port, *in_port, *out_port;
   MMAL_BUFFER_HEADER_T **other_buffer, *in = 0, *out = 0;
   MMAL_STATUS_T status;

   if (module->error)
   {
      mmal_queue_put(port->priv->module->queue, buffer);
      return MMAL_SUCCESS; /* Just do nothing */
   }

   in_port = port->component->input[port->index];
   out_port = port->component->output[port->index];

   if (port->type == MMAL_PORT_TYPE_INPUT)
   {
      other_port = &out_port;
      other_buffer = &out;
      in = buffer;
   }
   else
   {
      other_port = &in_port;
      other_buffer = &in;
      out = buffer;
   }

   /* Get a buffer header from the matching port */
   *other_buffer = mmal_queue_get((*other_port)->priv->module->queue);
   if (!*other_buffer)
   {
      /* None available. Just queue the buffer header for now. */
      mmal_queue_put(port->priv->module->queue, buffer);
      return MMAL_SUCCESS;
   }

   /* Copy our input buffer header */
   status = mmal_buffer_header_replicate(out, in);
   if (status != MMAL_SUCCESS)
      goto error;

   /* Consume the input buffer */
   in->length = 0;

   /* Send buffers back */
   mmal_port_buffer_header_callback(in_port, in);
   mmal_port_buffer_header_callback(out_port, out);

   return MMAL_SUCCESS;

 error:
   mmal_queue_put(in_port->priv->module->queue, in);
   mmal_queue_put(out_port->priv->module->queue, out);
   status = mmal_event_error_send(port->component, status);
   if (status != MMAL_SUCCESS)
   {
      LOG_ERROR("unable to send an error event buffer (%i)", (int)status);
      return MMAL_SUCCESS;
   }
   module->error = 1;
   return MMAL_SUCCESS;
}