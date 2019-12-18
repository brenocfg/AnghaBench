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
struct sockaddr {int dummy; } ;
struct proc {int dummy; } ;
struct ctl_cb {int /*<<< orphan*/  userdata; int /*<<< orphan*/  sac; TYPE_1__* kctl; } ;
struct TYPE_2__ {int (* bind ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  kctlref; } ;

/* Variables and functions */
 int EINVAL ; 
 int ctl_setup_kctl (struct socket*,struct sockaddr*,struct proc*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ctl_bind(struct socket *so, struct sockaddr *nam, struct proc *p)
{
	int error = 0;
	struct ctl_cb *kcb = (struct ctl_cb *)so->so_pcb;

	if (kcb == NULL) {
		panic("ctl_bind so_pcb null\n");
	}

	error = ctl_setup_kctl(so, nam, p);
	if (error) {
		return (error);
	}

	if (kcb->kctl == NULL) {
		panic("ctl_bind kctl null\n");
	}

	if (kcb->kctl->bind == NULL) {
		return (EINVAL);
	}

	socket_unlock(so, 0);
	error = (*kcb->kctl->bind)(kcb->kctl->kctlref, &kcb->sac, &kcb->userdata);
	socket_lock(so, 0);

	return (error);
}