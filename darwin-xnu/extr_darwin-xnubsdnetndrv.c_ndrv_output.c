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
struct socket {int dummy; } ;
struct ndrv_cb {int /*<<< orphan*/  nd_proto_family; struct ifnet* nd_if; } ;
struct mbuf {int m_flags; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int M_PKTHDR ; 
 int ifnet_output_raw (struct ifnet*,int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int /*<<< orphan*/ ) ; 
 struct ndrv_cb* sotondrvcb (struct socket*) ; 

__attribute__((used)) static int
ndrv_output(struct mbuf *m, struct socket *so)
{
    struct ndrv_cb *np = sotondrvcb(so);
	struct ifnet *ifp = np->nd_if;
    int	result = 0;

#if NDRV_DEBUG
	printf("NDRV output: %x, %x, %x\n", m, so, np);
#endif

	/*
	 * No header is a format error
	 */
	if ((m->m_flags&M_PKTHDR) == 0)
		return(EINVAL);

	/* Unlock before calling ifnet_output */
	socket_unlock(so, 0);

	/*
     * Call DLIL if we can. DLIL is much safer than calling the
     * ifp directly.
     */
	result = ifnet_output_raw(ifp, np->nd_proto_family, m);

	socket_lock(so, 0);

	return (result);
}