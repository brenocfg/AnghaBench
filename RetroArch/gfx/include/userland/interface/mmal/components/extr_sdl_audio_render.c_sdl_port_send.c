#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ length; scalar_t__ cmd; } ;
struct TYPE_15__ {scalar_t__ status; int /*<<< orphan*/  queue; } ;
struct TYPE_14__ {TYPE_1__* priv; } ;
struct TYPE_13__ {TYPE_3__* component; } ;
struct TYPE_12__ {TYPE_4__* module; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_PORT_T ;
typedef  TYPE_3__ MMAL_COMPONENT_T ;
typedef  TYPE_4__ MMAL_COMPONENT_MODULE_T ;
typedef  TYPE_5__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,int,TYPE_2__*) ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_port_buffer_header_callback (TYPE_2__*,TYPE_5__*) ; 
 int /*<<< orphan*/  mmal_queue_put (int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static MMAL_STATUS_T sdl_port_send(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
   MMAL_COMPONENT_T *component = port->component;
   MMAL_COMPONENT_MODULE_T *module = component->priv->module;

   /* Handle event buffers */
   if (buffer->cmd)
   {
      LOG_ERROR("discarding event %i on port %p", (int)buffer->cmd, port);
      buffer->length = 0;
      mmal_port_buffer_header_callback(port, buffer);
      return MMAL_SUCCESS;
   }

   if (module->status != MMAL_SUCCESS)
      return module->status;

   mmal_queue_put(module->queue, buffer);

   return MMAL_SUCCESS;
}