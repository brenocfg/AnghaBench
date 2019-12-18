#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ length; } ;
struct TYPE_12__ {int /*<<< orphan*/  queue; } ;
struct TYPE_11__ {TYPE_1__* priv; } ;
struct TYPE_10__ {TYPE_3__* clock; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_PORT_T ;
typedef  TYPE_3__ MMAL_PORT_CLOCK_T ;
typedef  TYPE_4__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_port_clock_process_buffer (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  mmal_queue_put (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_port_clock_send(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
   MMAL_PORT_CLOCK_T *priv_clock = port->priv->clock;

   if (buffer->length)
      return mmal_port_clock_process_buffer(port, buffer);

   /* Queue empty buffers to be used later when forwarding clock updates */
   mmal_queue_put(priv_clock->queue, buffer);

   return MMAL_SUCCESS;
}