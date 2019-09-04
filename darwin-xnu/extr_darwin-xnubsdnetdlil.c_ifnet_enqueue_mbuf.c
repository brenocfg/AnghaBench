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
struct mbuf {int m_flags; int /*<<< orphan*/ * m_nextpkt; } ;
struct ifnet {int if_eflags; int if_flags; } ;
typedef  int /*<<< orphan*/  errno_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENETDOWN ; 
 int /*<<< orphan*/  ENXIO ; 
 int IFEF_TXSTART ; 
 int IFF_UP ; 
 int /*<<< orphan*/  IF_FULLY_ATTACHED (struct ifnet*) ; 
 int M_PKTHDR ; 
 int /*<<< orphan*/  QP_MBUF ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ifnet_enqueue_common (struct ifnet*,struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  m_freem_list (struct mbuf*) ; 

errno_t
ifnet_enqueue_mbuf(struct ifnet *ifp, struct mbuf *m, boolean_t flush,
    boolean_t *pdrop)
{
	if (ifp == NULL || m == NULL || !(m->m_flags & M_PKTHDR) ||
	    m->m_nextpkt != NULL) {
		if (m != NULL) {
			m_freem_list(m);
			*pdrop = TRUE;
		}
		return (EINVAL);
	} else if (!(ifp->if_eflags & IFEF_TXSTART) ||
	    !IF_FULLY_ATTACHED(ifp)) {
		/* flag tested without lock for performance */
		m_freem(m);
		*pdrop = TRUE;
		return (ENXIO);
	} else if (!(ifp->if_flags & IFF_UP)) {
		m_freem(m);
		*pdrop = TRUE;
		return (ENETDOWN);
	}

	return (ifnet_enqueue_common(ifp, m, QP_MBUF, flush, pdrop));
}