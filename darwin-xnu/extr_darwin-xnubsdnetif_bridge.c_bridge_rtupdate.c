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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
struct bridge_softc {scalar_t__ sc_brtcnt; scalar_t__ sc_brtmax; scalar_t__ sc_brttimeout; int /*<<< orphan*/  sc_brtexceeded; } ;
struct bridge_rtnode {scalar_t__ brt_flags; int brt_vlan; scalar_t__ brt_expire; struct bridge_iflist* brt_dst; int /*<<< orphan*/  brt_addr; } ;
struct bridge_iflist {scalar_t__ bif_addrmax; scalar_t__ bif_addrcnt; int bif_ifflags; int /*<<< orphan*/  bif_addrexceeded; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRIDGE_LOCK_ASSERT_HELD (struct bridge_softc*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 scalar_t__ ETHER_IS_MULTICAST (scalar_t__ const*) ; 
 scalar_t__ IFBAF_DYNAMIC ; 
 scalar_t__ IFBAF_STICKY ; 
 scalar_t__ IFBAF_TYPEMASK ; 
 int IFBIF_STICKY ; 
 int /*<<< orphan*/  bridge_in_bsd_mode (struct bridge_softc*) ; 
 int bridge_rtnode_insert (struct bridge_softc*,struct bridge_rtnode*) ; 
 struct bridge_rtnode* bridge_rtnode_lookup (struct bridge_softc*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  bridge_rtnode_pool ; 
 int /*<<< orphan*/  bzero (struct bridge_rtnode*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__ const*,int /*<<< orphan*/ ) ; 
 scalar_t__ net_uptime () ; 
 struct bridge_rtnode* zalloc_noblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,struct bridge_rtnode*) ; 

__attribute__((used)) static int
bridge_rtupdate(struct bridge_softc *sc, const uint8_t *dst, uint16_t vlan,
	struct bridge_iflist *bif, int setflags, uint8_t flags)
{
	struct bridge_rtnode *brt;
	int error;

	BRIDGE_LOCK_ASSERT_HELD(sc);
	ASSERT(bridge_in_bsd_mode(sc));

	/* Check the source address is valid and not multicast. */
	if (ETHER_IS_MULTICAST(dst) ||
	    (dst[0] == 0 && dst[1] == 0 && dst[2] == 0 &&
	    dst[3] == 0 && dst[4] == 0 && dst[5] == 0) != 0)
		return (EINVAL);


	/* 802.1p frames map to vlan 1 */
	if (vlan == 0)
		vlan = 1;

	/*
	 * A route for this destination might already exist.  If so,
	 * update it, otherwise create a new one.
	 */
	if ((brt = bridge_rtnode_lookup(sc, dst, vlan)) == NULL) {
		if (sc->sc_brtcnt >= sc->sc_brtmax) {
			sc->sc_brtexceeded++;
			return (ENOSPC);
		}
		/* Check per interface address limits (if enabled) */
		if (bif->bif_addrmax && bif->bif_addrcnt >= bif->bif_addrmax) {
			bif->bif_addrexceeded++;
			return (ENOSPC);
		}

		/*
		 * Allocate a new bridge forwarding node, and
		 * initialize the expiration time and Ethernet
		 * address.
		 */
		brt = zalloc_noblock(bridge_rtnode_pool);
		if (brt == NULL)
			return (ENOMEM);
		bzero(brt, sizeof(struct bridge_rtnode));

		if (bif->bif_ifflags & IFBIF_STICKY)
			brt->brt_flags = IFBAF_STICKY;
		else
			brt->brt_flags = IFBAF_DYNAMIC;

		memcpy(brt->brt_addr, dst, ETHER_ADDR_LEN);
		brt->brt_vlan = vlan;


		if ((error = bridge_rtnode_insert(sc, brt)) != 0) {
			zfree(bridge_rtnode_pool, brt);
			return (error);
		}
		brt->brt_dst = bif;
		bif->bif_addrcnt++;
#if BRIDGE_DEBUG
		if (if_bridge_debug & BR_DBGF_RT_TABLE)
			printf("%s: added %02x:%02x:%02x:%02x:%02x:%02x "
			    "on %s count %u hashsize %u\n", __func__,
			    dst[0], dst[1], dst[2], dst[3], dst[4], dst[5],
			    sc->sc_ifp->if_xname, sc->sc_brtcnt,
			    sc->sc_rthash_size);
#endif
	}

	if ((brt->brt_flags & IFBAF_TYPEMASK) == IFBAF_DYNAMIC &&
	    brt->brt_dst != bif) {
		brt->brt_dst->bif_addrcnt--;
		brt->brt_dst = bif;
		brt->brt_dst->bif_addrcnt++;
	}

	if ((flags & IFBAF_TYPEMASK) == IFBAF_DYNAMIC) {
		unsigned long now;

		now = (unsigned long) net_uptime();
		brt->brt_expire = now + sc->sc_brttimeout;
	}
	if (setflags)
		brt->brt_flags = flags;


	return (0);
}