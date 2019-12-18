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
struct TYPE_8__ {int /*<<< orphan*/  clock; } ;
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {TYPE_3__* clock; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_PORT_T ;
typedef  TYPE_3__ MMAL_PORT_CLOCK_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_FALSE ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_clock_active_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mmal_clock_is_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_port_clock_flush (TYPE_2__*) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_port_clock_disable(MMAL_PORT_T *port)
{
   MMAL_PORT_CLOCK_T *priv_clock = port->priv->clock;

   if (mmal_clock_is_active(priv_clock->clock))
      mmal_clock_active_set(priv_clock->clock, MMAL_FALSE);

   mmal_port_clock_flush(port);

   return MMAL_SUCCESS;
}