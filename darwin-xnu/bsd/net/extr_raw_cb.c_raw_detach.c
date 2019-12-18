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
struct socket {int /*<<< orphan*/  so_flags; scalar_t__ so_pcb; } ;
struct rawcb {struct socket* rcb_socket; scalar_t__ rcb_laddr; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct rawcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_PCB ; 
 int /*<<< orphan*/  SOF_PCBCLEARING ; 
 int /*<<< orphan*/  dtom (scalar_t__) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_try_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_mtx ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sofree (struct socket*) ; 

void
raw_detach(struct rawcb *rp)
{
	struct socket *so = rp->rcb_socket;

	so->so_pcb = 0;
	so->so_flags |= SOF_PCBCLEARING;
	sofree(so);
	if (!lck_mtx_try_lock(raw_mtx)) {
		socket_unlock(so, 0);
		lck_mtx_lock(raw_mtx);
		socket_lock(so, 0);
	}
	LIST_REMOVE(rp, list);
	lck_mtx_unlock(raw_mtx);
#ifdef notdef
	if (rp->rcb_laddr)
		m_freem(dtom(rp->rcb_laddr));
	rp->rcb_laddr = 0;
#endif
	rp->rcb_socket = NULL;
	FREE((caddr_t)(rp), M_PCB);
}