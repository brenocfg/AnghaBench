#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket {int so_state; int /*<<< orphan*/  so_flags; scalar_t__ so_pcb; } ;
struct TYPE_4__ {int /*<<< orphan*/  sc_unit; } ;
struct ctl_cb {int /*<<< orphan*/ * userdata; TYPE_2__ sac; TYPE_1__* kctl; } ;
struct TYPE_3__ {int /*<<< orphan*/  kctlref; int /*<<< orphan*/  (* disconnect ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * bind; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOF_PCBCLEARING ; 
 int SS_ISCONNECTED ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soisdisconnected (struct socket*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ctl_detach(struct socket *so)
{
	struct ctl_cb 	*kcb = (struct ctl_cb *)so->so_pcb;

	if (kcb == 0)
		return (0);

	if (kcb->kctl != NULL && kcb->kctl->bind != NULL &&
	    kcb->userdata != NULL && !(so->so_state & SS_ISCONNECTED)) {
		// The unit was bound, but not connected
		// Invoke the disconnected call to cleanup
		if (kcb->kctl->disconnect != NULL) {
			socket_unlock(so, 0);
			(*kcb->kctl->disconnect)(kcb->kctl->kctlref,
			    kcb->sac.sc_unit, kcb->userdata);
			socket_lock(so, 0);
		}
	}

	soisdisconnected(so);
	so->so_flags |= SOF_PCBCLEARING;
	return (0);
}