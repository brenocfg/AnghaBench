#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct socket {int /*<<< orphan*/  so_options; int /*<<< orphan*/  so_flags; void* so_pcb; } ;
struct proc {int dummy; } ;
struct TYPE_5__ {scalar_t__ sp_protocol; } ;
struct TYPE_6__ {TYPE_1__ rcb_proto; int /*<<< orphan*/ * rcb_faddr; int /*<<< orphan*/ * rcb_laddr; } ;
struct keycb {TYPE_2__ kp_raw; scalar_t__ kp_registered; scalar_t__ kp_promisc; } ;
typedef  void* caddr_t ;
struct TYPE_8__ {int /*<<< orphan*/  any_count; int /*<<< orphan*/  key_count; } ;
struct TYPE_7__ {int (* pru_attach ) (struct socket*,int,struct proc*) ;} ;

/* Variables and functions */
 int EISCONN ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  M_PCB ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ PF_KEY ; 
 int /*<<< orphan*/  SOF_PCBCLEARING ; 
 int /*<<< orphan*/  SO_USELOOPBACK ; 
 int /*<<< orphan*/  _FREE (struct keycb*,int /*<<< orphan*/ ) ; 
 scalar_t__ _MALLOC (int,int /*<<< orphan*/ ,int) ; 
 TYPE_4__ key_cb ; 
 int /*<<< orphan*/  key_dst ; 
 int /*<<< orphan*/  key_src ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 TYPE_3__ raw_usrreqs ; 
 int /*<<< orphan*/  soisconnected (struct socket*) ; 
 scalar_t__ sotorawcb (struct socket*) ; 
 int stub1 (struct socket*,int,struct proc*) ; 

__attribute__((used)) static int
key_attach(struct socket *so, int proto, struct proc *p)
{
	struct keycb *kp;
	int error;

	if (sotorawcb(so) != 0)
		return EISCONN;	/* XXX panic? */
	kp = (struct keycb *)_MALLOC(sizeof (*kp), M_PCB,
	    M_WAITOK | M_ZERO); /* XXX */
	if (kp == 0)
		return ENOBUFS;

	so->so_pcb = (caddr_t)kp;
	kp->kp_promisc = kp->kp_registered = 0;
	kp->kp_raw.rcb_laddr = &key_src;
	kp->kp_raw.rcb_faddr = &key_dst;

	error = raw_usrreqs.pru_attach(so, proto, p);
	kp = (struct keycb *)sotorawcb(so);
	if (error) {
		_FREE(kp, M_PCB);
		so->so_pcb = (caddr_t) 0;
		so->so_flags |= SOF_PCBCLEARING;
		printf("key_usrreq: key_usrreq results %d\n", error);
		return error;
	}

	/* so is already locked when calling key_attach */
	if (kp->kp_raw.rcb_proto.sp_protocol == PF_KEY) /* XXX: AF_KEY */
		key_cb.key_count++;
	key_cb.any_count++;
	soisconnected(so);
	so->so_options |= SO_USELOOPBACK;

	return 0;
}