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

/* Variables and functions */
 int CVMX_PKO_ILLEGAL_QUEUE ; 
 int CVMX_PKO_MAX_PORTS_INTERFACE0 ; 
 int CVMX_PKO_MAX_PORTS_INTERFACE1 ; 
 int CVMX_PKO_QUEUES_PER_PORT_INTERFACE0 ; 
 int CVMX_PKO_QUEUES_PER_PORT_INTERFACE1 ; 
 int CVMX_PKO_QUEUES_PER_PORT_LOOP ; 
 int CVMX_PKO_QUEUES_PER_PORT_PCI ; 

__attribute__((used)) static inline int cvmx_pko_get_base_queue_per_core(int port, int core)
{
#ifndef CVMX_HELPER_PKO_MAX_PORTS_INTERFACE0
#define CVMX_HELPER_PKO_MAX_PORTS_INTERFACE0 16
#endif
#ifndef CVMX_HELPER_PKO_MAX_PORTS_INTERFACE1
#define CVMX_HELPER_PKO_MAX_PORTS_INTERFACE1 16
#endif

	if (port < CVMX_PKO_MAX_PORTS_INTERFACE0)
		return port * CVMX_PKO_QUEUES_PER_PORT_INTERFACE0 + core;
	else if (port >= 16 && port < 16 + CVMX_PKO_MAX_PORTS_INTERFACE1)
		return CVMX_PKO_MAX_PORTS_INTERFACE0 *
		    CVMX_PKO_QUEUES_PER_PORT_INTERFACE0 + (port -
							   16) *
		    CVMX_PKO_QUEUES_PER_PORT_INTERFACE1 + core;
	else if ((port >= 32) && (port < 36))
		return CVMX_PKO_MAX_PORTS_INTERFACE0 *
		    CVMX_PKO_QUEUES_PER_PORT_INTERFACE0 +
		    CVMX_PKO_MAX_PORTS_INTERFACE1 *
		    CVMX_PKO_QUEUES_PER_PORT_INTERFACE1 + (port -
							   32) *
		    CVMX_PKO_QUEUES_PER_PORT_PCI;
	else if ((port >= 36) && (port < 40))
		return CVMX_PKO_MAX_PORTS_INTERFACE0 *
		    CVMX_PKO_QUEUES_PER_PORT_INTERFACE0 +
		    CVMX_PKO_MAX_PORTS_INTERFACE1 *
		    CVMX_PKO_QUEUES_PER_PORT_INTERFACE1 +
		    4 * CVMX_PKO_QUEUES_PER_PORT_PCI + (port -
							36) *
		    CVMX_PKO_QUEUES_PER_PORT_LOOP;
	else
		/* Given the limit on the number of ports we can map to
		 * CVMX_MAX_OUTPUT_QUEUES_STATIC queues (currently 256,
		 * divided among all cores), the remaining unmapped ports
		 * are assigned an illegal queue number */
		return CVMX_PKO_ILLEGAL_QUEUE;
}