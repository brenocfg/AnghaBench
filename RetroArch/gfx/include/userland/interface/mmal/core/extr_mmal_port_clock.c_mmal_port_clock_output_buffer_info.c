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
struct TYPE_6__ {scalar_t__ buffer_info_reporting; } ;
typedef  TYPE_3__ MMAL_PORT_T ;
typedef  int /*<<< orphan*/  MMAL_CLOCK_BUFFER_INFO_T ;

/* Variables and functions */
 int /*<<< orphan*/  mmal_port_clock_forward_output_buffer_info (TYPE_3__*,int /*<<< orphan*/  const*) ; 

void mmal_port_clock_output_buffer_info(MMAL_PORT_T *port, const MMAL_CLOCK_BUFFER_INFO_T *info)
{
   if (port->priv->clock->buffer_info_reporting)
      mmal_port_clock_forward_output_buffer_info(port, info);
}