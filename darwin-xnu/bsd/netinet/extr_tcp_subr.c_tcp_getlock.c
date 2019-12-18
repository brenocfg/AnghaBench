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
struct socket {scalar_t__ so_usecount; int so_flags; TYPE_2__* so_proto; scalar_t__ so_pcb; } ;
struct mptcb {int /*<<< orphan*/  mpt_mpte; } ;
struct inpcb {int /*<<< orphan*/  inpcb_mtx; } ;
typedef  int /*<<< orphan*/  lck_mtx_t ;
struct TYPE_4__ {TYPE_1__* pr_domain; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dom_mtx; } ;

/* Variables and functions */
 int SOF_MP_SUBFLOW ; 
 int /*<<< orphan*/ * mpte_getlock (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*,struct socket*,scalar_t__,...) ; 
 int /*<<< orphan*/  solockhistory_nr (struct socket*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 
 int /*<<< orphan*/  sototcpcb (struct socket*) ; 
 struct mptcb* tptomptp (int /*<<< orphan*/ ) ; 

lck_mtx_t *
tcp_getlock(struct socket *so, int flags)
{
	struct inpcb *inp = sotoinpcb(so);

	if (so->so_pcb)  {
		if (so->so_usecount < 0)
			panic("tcp_getlock: so=%p usecount=%x lrh= %s\n",
			    so, so->so_usecount, solockhistory_nr(so));

		if (so->so_flags & SOF_MP_SUBFLOW) {
			struct mptcb *mp_tp = tptomptp(sototcpcb(so));

			return (mpte_getlock(mp_tp->mpt_mpte, flags));
		} else {
			return (&inp->inpcb_mtx);
		}
	} else {
		panic("tcp_getlock: so=%p NULL so_pcb %s\n",
		    so, solockhistory_nr(so));
		return (so->so_proto->pr_domain->dom_mtx);
	}
}