#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ length; } ;
struct TYPE_11__ {int /*<<< orphan*/  queue; } ;
struct TYPE_10__ {TYPE_1__* priv; } ;
struct TYPE_9__ {TYPE_3__* module; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_PORT_T ;
typedef  TYPE_3__ MMAL_PORT_MODULE_T ;
typedef  TYPE_4__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_port_buffer_header_callback (TYPE_2__*,TYPE_4__*) ; 
 TYPE_4__* mmal_queue_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static MMAL_STATUS_T container_port_flush(MMAL_PORT_T *port)
{
   MMAL_PORT_MODULE_T *port_module = port->priv->module;
   MMAL_BUFFER_HEADER_T *buffer;

   /* Flush buffers that our component is holding on to.
    * If the reading thread is holding onto a buffer it will send it back ASAP as well
    * so no need to care about that.  */
   buffer = mmal_queue_get(port_module->queue);
   while(buffer)
   {
      buffer->length = 0;
      mmal_port_buffer_header_callback(port, buffer);
      buffer = mmal_queue_get(port_module->queue);
   }

   return MMAL_SUCCESS;
}