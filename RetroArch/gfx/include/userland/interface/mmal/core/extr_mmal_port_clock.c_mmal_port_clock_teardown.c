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
struct TYPE_7__ {TYPE_2__* priv; } ;
struct TYPE_6__ {TYPE_1__* clock; } ;
struct TYPE_5__ {int /*<<< orphan*/  clock; int /*<<< orphan*/  queue; } ;
typedef  TYPE_3__ MMAL_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  mmal_clock_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_queue_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mmal_port_clock_teardown(MMAL_PORT_T *port)
{
   if (!port)
      return;
   mmal_queue_destroy(port->priv->clock->queue);
   mmal_clock_destroy(port->priv->clock->clock);
}