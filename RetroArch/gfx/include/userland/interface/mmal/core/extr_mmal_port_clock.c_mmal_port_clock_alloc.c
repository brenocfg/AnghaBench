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
 int /*<<< orphan*/ * mmal_port_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ mmal_port_clock_setup (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_port_free (int /*<<< orphan*/ *) ; 

MMAL_PORT_T* mmal_port_clock_alloc(MMAL_COMPONENT_T *component, unsigned int extra_size,
                                   MMAL_PORT_CLOCK_EVENT_CB event_cb)
{
   MMAL_PORT_T *port;

   port = mmal_port_alloc(component, MMAL_PORT_TYPE_CLOCK,
                          extra_size + sizeof(MMAL_PORT_CLOCK_T));
   if (!port)
      return NULL;

   if (mmal_port_clock_setup(port, extra_size, event_cb) != MMAL_SUCCESS)
   {
      mmal_port_free(port);
      return NULL;
   }

   return port;
}