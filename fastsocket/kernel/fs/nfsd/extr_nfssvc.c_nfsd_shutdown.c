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
 int /*<<< orphan*/  lockd_down () ; 
 int /*<<< orphan*/  nfs4_state_shutdown () ; 
 int /*<<< orphan*/  nfsd_racache_shutdown () ; 
 int nfsd_up ; 

__attribute__((used)) static void nfsd_shutdown(void)
{
	/*
	 * write_ports can create the server without actually starting
	 * any threads--if we get shut down before any threads are
	 * started, then nfsd_last_thread will be run before any of this
	 * other initialization has been done.
	 */
	if (!nfsd_up)
		return;
	nfs4_state_shutdown();
	lockd_down();
	nfsd_racache_shutdown();
	nfsd_up = false;
}