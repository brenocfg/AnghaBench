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
struct knote {scalar_t__ kn_hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  KNOTE_DETACH (int /*<<< orphan*/ *,struct knote*) ; 
 int /*<<< orphan*/  NECP_FD_LOCK (struct necp_fd_data*) ; 
 int /*<<< orphan*/  NECP_FD_UNLOCK (struct necp_fd_data*) ; 

__attribute__((used)) static void
necp_fd_knrdetach(struct knote *kn)
{
	struct necp_fd_data *fd_data = (struct necp_fd_data *)kn->kn_hook;
	struct selinfo *si = &fd_data->si;

	NECP_FD_LOCK(fd_data);
	KNOTE_DETACH(&si->si_note, kn);
	NECP_FD_UNLOCK(fd_data);
}