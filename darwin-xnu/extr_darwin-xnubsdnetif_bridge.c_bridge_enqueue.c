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
struct TYPE_2__ {int len; } ;
struct mbuf {short m_flags; TYPE_1__ m_pkthdr; struct mbuf* m_nextpkt; } ;
struct ifnet {int dummy; } ;
struct flowadv {scalar_t__ code; int /*<<< orphan*/  member_0; } ;
struct bridge_softc {int /*<<< orphan*/  sc_ifp; } ;
typedef  int errno_t ;

/* Variables and functions */
 int EQFULL ; 
 int EQSUSPENDED ; 
 scalar_t__ FADV_FLOW_CONTROLLED ; 
 int /*<<< orphan*/  FADV_SUCCESS ; 
 scalar_t__ FADV_SUSPENDED ; 
 short M_PROTO1 ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bridge_finalize_cksum (struct ifnet*,struct mbuf*) ; 
 int dlil_output (struct ifnet*,int /*<<< orphan*/ ,struct mbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct flowadv*) ; 
 int /*<<< orphan*/  ifnet_stat_increment_out (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int
bridge_enqueue(struct bridge_softc *sc, struct ifnet *dst_ifp, struct mbuf *m)
{
	int len, error = 0;
	short mflags;
	struct mbuf *m0;

	VERIFY(dst_ifp != NULL);

	/*
	 * We may be sending a fragment so traverse the mbuf
	 *
	 * NOTE: bridge_fragment() is called only when PFIL_HOOKS is enabled.
	 */
	for (; m; m = m0) {
		errno_t _error;
		struct flowadv adv = { FADV_SUCCESS };

		m0 = m->m_nextpkt;
		m->m_nextpkt = NULL;

		len = m->m_pkthdr.len;
		mflags = m->m_flags;
		m->m_flags |= M_PROTO1; /* set to avoid loops */

		bridge_finalize_cksum(dst_ifp, m);

#if HAS_IF_CAP
		/*
		 * If underlying interface can not do VLAN tag insertion itself
		 * then attach a packet tag that holds it.
		 */
		if ((m->m_flags & M_VLANTAG) &&
		    (dst_ifp->if_capenable & IFCAP_VLAN_HWTAGGING) == 0) {
			m = ether_vlanencap(m, m->m_pkthdr.ether_vtag);
			if (m == NULL) {
				printf("%s: %s: unable to prepend VLAN "
				    "header\n", __func__, dst_ifp->if_xname);
				(void) ifnet_stat_increment_out(dst_ifp,
				    0, 0, 1);
				continue;
			}
			m->m_flags &= ~M_VLANTAG;
		}
#endif /* HAS_IF_CAP */

		_error = dlil_output(dst_ifp, 0, m, NULL, NULL, 1, &adv);

		/* Preserve existing error value */
		if (error == 0) {
			if (_error != 0)
				error = _error;
			else if (adv.code == FADV_FLOW_CONTROLLED)
				error = EQFULL;
			else if (adv.code == FADV_SUSPENDED)
				error = EQSUSPENDED;
		}

		if (_error == 0) {
			(void) ifnet_stat_increment_out(sc->sc_ifp, 1, len, 0);
		} else {
			(void) ifnet_stat_increment_out(sc->sc_ifp, 0, 0, 1);
		}
	}

	return (error);
}