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
struct ndrv_cb {scalar_t__ nd_faddr; struct socket* nd_socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_IFADDR ; 
 int SOF_MP_SUBFLOW ; 
 int SS_NOFDREF ; 
 int /*<<< orphan*/  ndrv_do_detach (struct ndrv_cb*) ; 
 int /*<<< orphan*/  soisdisconnected (struct socket*) ; 

__attribute__((used)) static int
ndrv_do_disconnect(struct ndrv_cb *np)
{
	struct socket * so = np->nd_socket;
#if NDRV_DEBUG
	printf("NDRV disconnect: %x\n", np);
#endif
	if (np->nd_faddr)
	{
        FREE(np->nd_faddr, M_IFADDR);
		np->nd_faddr = 0;
	}
	/*
	 * A multipath subflow socket would have its SS_NOFDREF set by default,
	 * so check for SOF_MP_SUBFLOW socket flag before detaching the PCB;
	 * when the socket is closed for real, SOF_MP_SUBFLOW would be cleared.
	 */
	if (!(so->so_flags & SOF_MP_SUBFLOW) && (so->so_state & SS_NOFDREF))
		ndrv_do_detach(np);
	soisdisconnected(so);
	return(0);
}