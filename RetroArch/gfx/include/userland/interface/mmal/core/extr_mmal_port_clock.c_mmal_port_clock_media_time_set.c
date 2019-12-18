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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_8__ {TYPE_2__* priv; } ;
struct TYPE_7__ {TYPE_1__* clock; } ;
struct TYPE_6__ {scalar_t__ is_reference; int /*<<< orphan*/  clock; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (char*) ; 
 scalar_t__ MMAL_SUCCESS ; 
 scalar_t__ mmal_clock_media_time_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mmal_port_clock_forward_media_time (TYPE_3__*,int /*<<< orphan*/ ) ; 

MMAL_STATUS_T mmal_port_clock_media_time_set(MMAL_PORT_T *port, int64_t media_time)
{
   MMAL_STATUS_T status;

   status = mmal_clock_media_time_set(port->priv->clock->clock, media_time);
   if (status != MMAL_SUCCESS)
   {
      LOG_DEBUG("clock media-time update ignored");
      return status;
   }

   if (port->priv->clock->is_reference)
      status = mmal_port_clock_forward_media_time(port, media_time);

   return status;
}