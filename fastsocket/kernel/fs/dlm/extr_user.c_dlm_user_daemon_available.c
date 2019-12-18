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
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlm_monitor_opened ; 
 scalar_t__ dlm_monitor_unused ; 
 int /*<<< orphan*/  dlm_our_nodeid () ; 

int dlm_user_daemon_available(void)
{
	/* dlm_controld hasn't started (or, has started, but not
	   properly populated configfs) */

	if (!dlm_our_nodeid())
		return 0;

	/* This is to deal with versions of dlm_controld that don't
	   know about the monitor device.  We assume that if the
	   dlm_controld was started (above), but the monitor device
	   was never opened, that it's an old version.  dlm_controld
	   should open the monitor device before populating configfs. */

	if (dlm_monitor_unused)
		return 1;

	return atomic_read(&dlm_monitor_opened) ? 1 : 0;
}