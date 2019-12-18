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
struct necp_fd_data {int dummy; } ;
struct knote {scalar_t__ kn_hook; } ;
struct kevent_internal_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NECP_FD_LOCK (struct necp_fd_data*) ; 
 int /*<<< orphan*/  NECP_FD_UNLOCK (struct necp_fd_data*) ; 
 int POLLIN ; 
 int /*<<< orphan*/  current_proc () ; 
 int necp_fd_poll (struct necp_fd_data*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
necp_fd_knrtouch(struct knote *kn, struct kevent_internal_s *kev)
{
#pragma unused(kev)
	struct necp_fd_data *fd_data;
	int revents;

	fd_data = (struct necp_fd_data *)kn->kn_hook;

	NECP_FD_LOCK(fd_data);
	revents = necp_fd_poll(fd_data, POLLIN, NULL, current_proc(), 1);
	NECP_FD_UNLOCK(fd_data);

	return ((revents & POLLIN) != 0);
}