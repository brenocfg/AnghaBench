#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int clock_num; TYPE_1__** clock; } ;
struct TYPE_5__ {scalar_t__ is_enabled; } ;
typedef  int /*<<< orphan*/  TIME_T ;
typedef  TYPE_1__ MMAL_PORT_T ;
typedef  TYPE_2__ MMAL_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  mmal_port_clock_media_time_set (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clock_set_media_time(MMAL_COMPONENT_T *component, TIME_T media_time)
{
   unsigned i;

   for (i = 0; i < component->clock_num; ++i)
   {
      MMAL_PORT_T *port = component->clock[i];
      if (port->is_enabled)
         mmal_port_clock_media_time_set(port, media_time);
   }
}