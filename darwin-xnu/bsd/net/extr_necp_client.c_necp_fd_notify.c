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
struct selinfo {int /*<<< orphan*/  si_note; } ;
struct necp_fd_data {struct selinfo si; } ;

/* Variables and functions */
 int /*<<< orphan*/  KNOTE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  NECP_FD_LOCK (struct necp_fd_data*) ; 
 int /*<<< orphan*/  NECP_FD_UNLOCK (struct necp_fd_data*) ; 
 int /*<<< orphan*/  selwakeup (struct selinfo*) ; 

__attribute__((used)) static void
necp_fd_notify(struct necp_fd_data *fd_data, bool locked)
{
	struct selinfo *si = &fd_data->si;

	if (!locked) {
		NECP_FD_LOCK(fd_data);
	}

	selwakeup(si);

	// use a non-zero hint to tell the notification from the
	// call done in kqueue_scan() which uses 0
	KNOTE(&si->si_note, 1); // notification

	if (!locked) {
		NECP_FD_UNLOCK(fd_data);
	}
}