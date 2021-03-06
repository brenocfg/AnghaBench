#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* priv; } ;
struct TYPE_7__ {TYPE_1__* clock; } ;
struct TYPE_6__ {int /*<<< orphan*/  queue; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_PORT_T ;
typedef  int /*<<< orphan*/  MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_port_buffer_header_callback (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mmal_queue_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_port_clock_flush(MMAL_PORT_T *port)
{
   MMAL_BUFFER_HEADER_T *buffer;

   /* Flush empty buffers */
   buffer = mmal_queue_get(port->priv->clock->queue);
   while (buffer)
   {
      mmal_port_buffer_header_callback(port, buffer);
      buffer = mmal_queue_get(port->priv->clock->queue);
   }

   return MMAL_SUCCESS;
}