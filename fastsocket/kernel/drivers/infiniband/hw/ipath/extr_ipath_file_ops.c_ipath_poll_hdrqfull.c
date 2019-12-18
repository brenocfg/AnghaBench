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
struct ipath_portdata {int poll_type; scalar_t__ port_hdrqfull; scalar_t__ port_hdrqfull_poll; } ;

/* Variables and functions */
 int IPATH_POLL_TYPE_OVERFLOW ; 
 unsigned int POLLIN ; 
 unsigned int POLLRDNORM ; 

__attribute__((used)) static unsigned ipath_poll_hdrqfull(struct ipath_portdata *pd)
{
	unsigned pollflag = 0;

	if ((pd->poll_type & IPATH_POLL_TYPE_OVERFLOW) &&
	    pd->port_hdrqfull != pd->port_hdrqfull_poll) {
		pollflag |= POLLIN | POLLRDNORM;
		pd->port_hdrqfull_poll = pd->port_hdrqfull;
	}

	return pollflag;
}