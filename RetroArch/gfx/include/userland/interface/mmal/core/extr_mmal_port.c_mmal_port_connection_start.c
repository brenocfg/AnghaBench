#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ type; TYPE_2__* priv; } ;
struct TYPE_10__ {TYPE_1__* core; } ;
struct TYPE_9__ {int /*<<< orphan*/ * pool_for_connection; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_PORT_T ;
typedef  int /*<<< orphan*/  MMAL_POOL_T ;

/* Variables and functions */
 scalar_t__ MMAL_PORT_TYPE_CLOCK ; 
 scalar_t__ MMAL_PORT_TYPE_INPUT ; 
 scalar_t__ MMAL_PORT_TYPE_OUTPUT ; 
 int /*<<< orphan*/  mmal_port_populate_clock_ports (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_port_populate_from_pool (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_port_connection_start(MMAL_PORT_T *port, MMAL_PORT_T *connected_port)
{
   MMAL_PORT_T *output = port->type == MMAL_PORT_TYPE_OUTPUT ? port : connected_port;
   MMAL_PORT_T *input = connected_port->type == MMAL_PORT_TYPE_INPUT ? connected_port : port;
   MMAL_POOL_T *pool = port->priv->core->pool_for_connection ?
      port->priv->core->pool_for_connection : connected_port->priv->core->pool_for_connection;
   MMAL_STATUS_T status;

   if (output->type == MMAL_PORT_TYPE_CLOCK && input->type == MMAL_PORT_TYPE_CLOCK)
   {
      /* Clock ports need buffers to send clock updates, so
       * populate both clock ports */
      status = mmal_port_populate_clock_ports(output, input, pool);
   }
   else
   {
      /* Put the buffers into the output port */
      status = mmal_port_populate_from_pool(output, pool);
   }

   return status;
}