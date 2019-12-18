#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct socket {scalar_t__ so_pcb; } ;
struct kctl {int /*<<< orphan*/  kctlref; int /*<<< orphan*/  (* rcvd ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  sc_unit; } ;
struct ctl_cb {int /*<<< orphan*/  userdata; TYPE_1__ sac; struct kctl* kctl; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ctl_sbrcv_trim (struct socket*) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ctl_usr_rcvd(struct socket *so, int flags)
{
	struct ctl_cb		*kcb = (struct ctl_cb *)so->so_pcb;
	struct kctl			*kctl;

	if ((kctl = kcb->kctl) == NULL) {
		return (EINVAL);
	}

	if (kctl->rcvd) {
		socket_unlock(so, 0);
		(*kctl->rcvd)(kctl->kctlref, kcb->sac.sc_unit, kcb->userdata, flags);
		socket_lock(so, 0);
	}

	ctl_sbrcv_trim(so);

	return (0);
}