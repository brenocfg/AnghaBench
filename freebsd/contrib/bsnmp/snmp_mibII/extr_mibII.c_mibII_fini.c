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
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fd_deselect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifmib_reg ; 
 int /*<<< orphan*/  ipForward_reg ; 
 int /*<<< orphan*/  ipmib_reg ; 
 int /*<<< orphan*/ * mibII_poll_timer ; 
 int mib_netsock ; 
 int /*<<< orphan*/  or_unregister (int /*<<< orphan*/ ) ; 
 int route ; 
 int /*<<< orphan*/ * route_fd ; 
 int /*<<< orphan*/  tcpmib_reg ; 
 int /*<<< orphan*/  timer_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udpmib_reg ; 

__attribute__((used)) static int
mibII_fini(void)
{
	if (mibII_poll_timer != NULL ) {
		timer_stop(mibII_poll_timer);
		mibII_poll_timer = NULL;
	}

	if (route_fd != NULL)
		fd_deselect(route_fd);
	if (route != -1)
		(void)close(route);
	if (mib_netsock != -1)
		(void)close(mib_netsock);
	/* XXX free memory */

	or_unregister(ipForward_reg);
	or_unregister(udpmib_reg);
	or_unregister(tcpmib_reg);
	or_unregister(ipmib_reg);
	or_unregister(ifmib_reg);

	return (0);
}