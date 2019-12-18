#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  last_ts; int /*<<< orphan*/  queue; } ;
struct TYPE_9__ {TYPE_1__* priv; TYPE_2__* component; } ;
struct TYPE_8__ {int /*<<< orphan*/ * clock; } ;
struct TYPE_7__ {TYPE_4__* module; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_PORT_T ;
typedef  TYPE_4__ MMAL_PORT_MODULE_T ;
typedef  int /*<<< orphan*/  MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  MMAL_TIME_UNKNOWN ; 
 int /*<<< orphan*/  mmal_port_buffer_header_callback (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_port_clock_request_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mmal_queue_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static MMAL_STATUS_T scheduler_port_flush(MMAL_PORT_T *port)
{
   MMAL_PORT_MODULE_T *port_module = port->priv->module;
   MMAL_BUFFER_HEADER_T *buffer;

   /* Flush buffers associated with pending clock requests */
   mmal_port_clock_request_flush(port->component->clock[0]);

   /* Flush buffers that our component is holding on to */
   buffer = mmal_queue_get(port_module->queue);
   while (buffer)
   {
      mmal_port_buffer_header_callback(port, buffer);
      buffer = mmal_queue_get(port_module->queue);
   }

   port->priv->module->last_ts = MMAL_TIME_UNKNOWN;
   return MMAL_SUCCESS;
}