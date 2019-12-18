#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct socket {scalar_t__ so_pcb; } ;
struct sockaddr {int dummy; } ;
struct proc {int dummy; } ;
struct TYPE_5__ {scalar_t__ sc_unit; } ;
struct ctl_cb {TYPE_2__ sac; TYPE_1__* kctl; int /*<<< orphan*/  userdata; } ;
struct TYPE_6__ {int /*<<< orphan*/  kcs_conn_fail; int /*<<< orphan*/  kcs_gencnt; int /*<<< orphan*/  kcs_pcbcount; } ;
struct TYPE_4__ {int (* connect ) (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  kcb_head; int /*<<< orphan*/  kctlref; int /*<<< orphan*/  (* disconnect ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ctl_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_mtx ; 
 int ctl_setup_kctl (struct socket*,struct sockaddr*,struct proc*) ; 
 TYPE_3__ kctlstat ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soisconnected (struct socket*) ; 
 int /*<<< orphan*/  soisconnecting (struct socket*) ; 
 int /*<<< orphan*/  soisdisconnected (struct socket*) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ctl_connect(struct socket *so, struct sockaddr *nam, struct proc *p)
{
	int error = 0;
	struct ctl_cb *kcb = (struct ctl_cb *)so->so_pcb;

	if (kcb == NULL) {
		panic("ctl_connect so_pcb null\n");
	}

	error = ctl_setup_kctl(so, nam, p);
	if (error) {
		return (error);
	}

	if (kcb->kctl == NULL) {
		panic("ctl_connect kctl null\n");
	}

	soisconnecting(so);
	socket_unlock(so, 0);
	error = (*kcb->kctl->connect)(kcb->kctl->kctlref, &kcb->sac, &kcb->userdata);
	socket_lock(so, 0);
	if (error) {
		goto end;
	}
	soisconnected(so);

end:
	if (error && kcb->kctl->disconnect) {
		/*
		 * XXX Make sure we Don't check the return value
		 * of disconnect here.
		 * ipsec/utun_ctl_disconnect will return error when
		 * disconnect gets called after connect failure.
		 * However if we decide to check for disconnect return
		 * value here. Please make sure to revisit
		 * ipsec/utun_ctl_disconnect.
		 */
		socket_unlock(so, 0);
		(*kcb->kctl->disconnect)(kcb->kctl->kctlref, kcb->sac.sc_unit, kcb->userdata);
		socket_lock(so, 0);
	}
	if (error) {
		soisdisconnected(so);
		lck_mtx_lock(ctl_mtx);
		TAILQ_REMOVE(&kcb->kctl->kcb_head, kcb, next);
		kcb->kctl = NULL;
		kcb->sac.sc_unit = 0;
		kctlstat.kcs_pcbcount--;
		kctlstat.kcs_gencnt++;
		kctlstat.kcs_conn_fail++;
		lck_mtx_unlock(ctl_mtx);
	}
	return (error);
}