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
struct TYPE_5__ {int /*<<< orphan*/  clock; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_PORT_T ;
typedef  int /*<<< orphan*/  MMAL_CLOCK_UPDATE_THRESHOLD_T ;

/* Variables and functions */
 int /*<<< orphan*/  mmal_clock_update_threshold_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

MMAL_STATUS_T mmal_port_clock_update_threshold_get(MMAL_PORT_T *port,
                                          MMAL_CLOCK_UPDATE_THRESHOLD_T *threshold)
{
   return mmal_clock_update_threshold_get(port->priv->clock->clock, threshold);
}