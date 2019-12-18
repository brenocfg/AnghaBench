#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  MMAL_PORT_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_CLOCK_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_CLOCK_EVENT_CB ;
typedef  int /*<<< orphan*/  MMAL_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_PORT_TYPE_CLOCK ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_port_clock_free (int /*<<< orphan*/ *) ; 
 scalar_t__ mmal_port_clock_setup (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** mmal_ports_alloc (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  vcos_free (int /*<<< orphan*/ **) ; 

MMAL_PORT_T **mmal_ports_clock_alloc(MMAL_COMPONENT_T *component, unsigned int ports_num,
                                     unsigned int extra_size, MMAL_PORT_CLOCK_EVENT_CB event_cb)
{
   unsigned int i;
   MMAL_PORT_T **ports;

   ports = mmal_ports_alloc(component, ports_num, MMAL_PORT_TYPE_CLOCK,
                            extra_size + sizeof(MMAL_PORT_CLOCK_T));
   if (!ports)
      return NULL;

   for (i = 0; i < ports_num; i++)
   {
      if (mmal_port_clock_setup(ports[i], extra_size, event_cb) != MMAL_SUCCESS)
         break;
   }

   if (i != ports_num)
   {
      for (ports_num = i, i = 0; i < ports_num; i++)
         mmal_port_clock_free(ports[i]);
      vcos_free(ports);
      return NULL;
   }

   return ports;
}