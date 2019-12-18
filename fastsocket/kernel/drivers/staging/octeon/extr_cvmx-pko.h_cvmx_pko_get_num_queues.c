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
 int CVMX_PKO_QUEUES_PER_PORT_INTERFACE0 ; 
 int CVMX_PKO_QUEUES_PER_PORT_INTERFACE1 ; 
 int CVMX_PKO_QUEUES_PER_PORT_LOOP ; 
 int CVMX_PKO_QUEUES_PER_PORT_PCI ; 

__attribute__((used)) static inline int cvmx_pko_get_num_queues(int port)
{
	if (port < 16)
		return CVMX_PKO_QUEUES_PER_PORT_INTERFACE0;
	else if (port < 32)
		return CVMX_PKO_QUEUES_PER_PORT_INTERFACE1;
	else if (port < 36)
		return CVMX_PKO_QUEUES_PER_PORT_PCI;
	else if (port < 40)
		return CVMX_PKO_QUEUES_PER_PORT_LOOP;
	else
		return 0;
}