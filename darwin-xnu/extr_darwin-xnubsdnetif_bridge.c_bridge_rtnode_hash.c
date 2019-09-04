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
typedef  size_t uint32_t ;
struct bridge_softc {int /*<<< orphan*/ * sc_rthash; } ;
struct bridge_rtnode {scalar_t__ brt_vlan; int /*<<< orphan*/  brt_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_LOCK_ASSERT_HELD (struct bridge_softc*) ; 
 int EEXIST ; 
 struct bridge_rtnode* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_AFTER (struct bridge_rtnode*,struct bridge_rtnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INSERT_BEFORE (struct bridge_rtnode*,struct bridge_rtnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct bridge_rtnode*,int /*<<< orphan*/ ) ; 
 struct bridge_rtnode* LIST_NEXT (struct bridge_rtnode*,int /*<<< orphan*/ ) ; 
 size_t bridge_rthash (struct bridge_softc*,int /*<<< orphan*/ ) ; 
 int bridge_rtnode_addr_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brt_hash ; 

__attribute__((used)) static int
bridge_rtnode_hash(struct bridge_softc *sc, struct bridge_rtnode *brt)
{
	struct bridge_rtnode *lbrt;
	uint32_t hash;
	int dir;

	BRIDGE_LOCK_ASSERT_HELD(sc);

	hash = bridge_rthash(sc, brt->brt_addr);

	lbrt = LIST_FIRST(&sc->sc_rthash[hash]);
	if (lbrt == NULL) {
		LIST_INSERT_HEAD(&sc->sc_rthash[hash], brt, brt_hash);
		goto out;
	}

	do {
		dir = bridge_rtnode_addr_cmp(brt->brt_addr, lbrt->brt_addr);
		if (dir == 0 && brt->brt_vlan == lbrt->brt_vlan) {
#if BRIDGE_DEBUG
			if (if_bridge_debug & BR_DBGF_RT_TABLE)
				printf("%s: %s EEXIST "
				    "%02x:%02x:%02x:%02x:%02x:%02x\n",
				    __func__, sc->sc_ifp->if_xname,
				    brt->brt_addr[0], brt->brt_addr[1],
				    brt->brt_addr[2], brt->brt_addr[3],
				    brt->brt_addr[4], brt->brt_addr[5]);
#endif
			return (EEXIST);
		}
		if (dir > 0) {
			LIST_INSERT_BEFORE(lbrt, brt, brt_hash);
			goto out;
		}
		if (LIST_NEXT(lbrt, brt_hash) == NULL) {
			LIST_INSERT_AFTER(lbrt, brt, brt_hash);
			goto out;
		}
		lbrt = LIST_NEXT(lbrt, brt_hash);
	} while (lbrt != NULL);

#if BRIDGE_DEBUG
	if (if_bridge_debug & BR_DBGF_RT_TABLE)
		printf("%s: %s impossible %02x:%02x:%02x:%02x:%02x:%02x\n",
		    __func__, sc->sc_ifp->if_xname,
		    brt->brt_addr[0], brt->brt_addr[1], brt->brt_addr[2],
		    brt->brt_addr[3], brt->brt_addr[4], brt->brt_addr[5]);
#endif

out:
	return (0);
}