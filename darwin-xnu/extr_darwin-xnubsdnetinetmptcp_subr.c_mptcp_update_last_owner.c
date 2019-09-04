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
struct socket {scalar_t__ last_pid; scalar_t__ last_upid; int /*<<< orphan*/  last_uuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  so_update_policy (struct socket*) ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mptcp_update_last_owner(struct socket *so, struct socket *mp_so)
{
	if (so->last_pid != mp_so->last_pid ||
	    so->last_upid != mp_so->last_upid) {
		so->last_upid = mp_so->last_upid;
		so->last_pid = mp_so->last_pid;
		uuid_copy(so->last_uuid, mp_so->last_uuid);
	}
	so_update_policy(so);
}