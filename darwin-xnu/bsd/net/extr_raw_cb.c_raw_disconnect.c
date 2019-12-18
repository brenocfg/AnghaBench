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
struct socket {int so_flags; int so_state; } ;
struct rawcb {scalar_t__ rcb_faddr; struct socket* rcb_socket; } ;

/* Variables and functions */
 int SOF_MP_SUBFLOW ; 
 int SS_NOFDREF ; 
 int /*<<< orphan*/  dtom (scalar_t__) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_detach (struct rawcb*) ; 

void
raw_disconnect(struct rawcb *rp)
{
	struct socket *so = rp->rcb_socket;

#ifdef notdef
	if (rp->rcb_faddr)
		m_freem(dtom(rp->rcb_faddr));
	rp->rcb_faddr = 0;
#endif
	/*
	 * A multipath subflow socket would have its SS_NOFDREF set by default,
	 * so check for SOF_MP_SUBFLOW socket flag before detaching the PCB;
	 * when the socket is closed for real, SOF_MP_SUBFLOW would be cleared.
	 */
	if (!(so->so_flags & SOF_MP_SUBFLOW) && (so->so_state & SS_NOFDREF))
		raw_detach(rp);
}