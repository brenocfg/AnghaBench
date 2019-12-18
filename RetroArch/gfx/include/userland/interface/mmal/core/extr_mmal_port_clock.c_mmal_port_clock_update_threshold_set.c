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
struct TYPE_6__ {scalar_t__ is_reference; int /*<<< orphan*/  clock; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_PORT_T ;
typedef  int /*<<< orphan*/  MMAL_CLOCK_UPDATE_THRESHOLD_T ;

/* Variables and functions */
 scalar_t__ MMAL_SUCCESS ; 
 scalar_t__ mmal_clock_update_threshold_set (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ mmal_port_clock_forward_update_threshold (TYPE_3__*,int /*<<< orphan*/  const*) ; 

MMAL_STATUS_T mmal_port_clock_update_threshold_set(MMAL_PORT_T *port,
                                                   const MMAL_CLOCK_UPDATE_THRESHOLD_T *threshold)
{
   MMAL_STATUS_T status;

   status = mmal_clock_update_threshold_set(port->priv->clock->clock, threshold);
   if (status != MMAL_SUCCESS)
      return status;

   if (port->priv->clock->is_reference)
      status = mmal_port_clock_forward_update_threshold(port, threshold);

   return status;
}