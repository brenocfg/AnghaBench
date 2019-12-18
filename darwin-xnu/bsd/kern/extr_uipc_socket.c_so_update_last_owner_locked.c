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
struct socket {scalar_t__ last_pid; scalar_t__ last_upid; int /*<<< orphan*/  so_vuuid; int /*<<< orphan*/  last_uuid; } ;
typedef  scalar_t__ proc_t ;

/* Variables and functions */
 scalar_t__ PROC_NULL ; 
 scalar_t__ current_proc () ; 
 int /*<<< orphan*/  proc_getexecutableuuid (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ proc_pid (scalar_t__) ; 
 int /*<<< orphan*/  proc_pidoriginatoruuid (int /*<<< orphan*/ ,int) ; 
 scalar_t__ proc_uniqueid (scalar_t__) ; 

void
so_update_last_owner_locked(struct socket *so, proc_t self)
{
	if (so->last_pid != 0) {
		/*
		 * last_pid and last_upid should remain zero for sockets
		 * created using sock_socket. The check above achieves that
		 */
		if (self == PROC_NULL)
			self = current_proc();

		if (so->last_upid != proc_uniqueid(self) ||
		    so->last_pid != proc_pid(self)) {
			so->last_upid = proc_uniqueid(self);
			so->last_pid = proc_pid(self);
			proc_getexecutableuuid(self, so->last_uuid,
			    sizeof (so->last_uuid));
		}
		proc_pidoriginatoruuid(so->so_vuuid, sizeof(so->so_vuuid));
	}
}