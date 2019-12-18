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
struct kctl {int /*<<< orphan*/  kcb_head; } ;
struct ctl_cb {struct kctl* kctl; } ;
struct TYPE_2__ {int /*<<< orphan*/  kcs_gencnt; int /*<<< orphan*/  kcs_pcbcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ctl_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_mtx ; 
 int /*<<< orphan*/  kcb_delete (struct ctl_cb*) ; 
 TYPE_1__ kctlstat ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  sofreelastref (struct socket*,int) ; 

__attribute__((used)) static int
ctl_sofreelastref(struct socket *so)
{
	struct ctl_cb 	*kcb = (struct ctl_cb *)so->so_pcb;

	so->so_pcb = 0;

	if (kcb != 0) {
		struct kctl		*kctl;
		if ((kctl = kcb->kctl) != 0) {
			lck_mtx_lock(ctl_mtx);
			TAILQ_REMOVE(&kctl->kcb_head, kcb, next);
			kctlstat.kcs_pcbcount--;
			kctlstat.kcs_gencnt++;
			lck_mtx_unlock(ctl_mtx);
		}
		kcb_delete(kcb);
	}
	sofreelastref(so, 1);
	return (0);
}