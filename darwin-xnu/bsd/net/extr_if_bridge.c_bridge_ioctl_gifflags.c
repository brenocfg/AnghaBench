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
struct ifbreq {int ifbr_stpflags; int ifbr_portno; int /*<<< orphan*/  ifbr_addrexceeded; int /*<<< orphan*/  ifbr_addrmax; int /*<<< orphan*/  ifbr_addrcnt; int /*<<< orphan*/  ifbr_ifsflags; int /*<<< orphan*/  ifbr_role; int /*<<< orphan*/  ifbr_proto; int /*<<< orphan*/  ifbr_path_cost; int /*<<< orphan*/  ifbr_priority; int /*<<< orphan*/  ifbr_state; int /*<<< orphan*/  ifbr_ifsname; } ;
struct bstp_port {int bp_flags; scalar_t__ bp_ptp_link; scalar_t__ bp_operedge; int /*<<< orphan*/  bp_role; int /*<<< orphan*/  bp_protover; int /*<<< orphan*/  bp_path_cost; int /*<<< orphan*/  bp_priority; int /*<<< orphan*/  bp_state; } ;
struct bridge_softc {int dummy; } ;
struct bridge_iflist {int /*<<< orphan*/  bif_addrexceeded; int /*<<< orphan*/  bif_addrmax; int /*<<< orphan*/  bif_addrcnt; TYPE_1__* bif_ifp; int /*<<< orphan*/  bif_ifflags; struct bstp_port bif_stp; } ;
struct TYPE_2__ {int if_index; } ;

/* Variables and functions */
 int BSTP_PORT_ADMCOST ; 
 int BSTP_PORT_ADMEDGE ; 
 int BSTP_PORT_AUTOEDGE ; 
 int BSTP_PORT_AUTOPTP ; 
 int ENOENT ; 
 int /*<<< orphan*/  IFBIF_BSTP_ADMCOST ; 
 int /*<<< orphan*/  IFBIF_BSTP_ADMEDGE ; 
 int /*<<< orphan*/  IFBIF_BSTP_AUTOEDGE ; 
 int /*<<< orphan*/  IFBIF_BSTP_AUTOPTP ; 
 int /*<<< orphan*/  IFBIF_BSTP_EDGE ; 
 int /*<<< orphan*/  IFBIF_BSTP_PTP ; 
 scalar_t__ bridge_in_bsd_mode (struct bridge_softc*) ; 
 struct bridge_iflist* bridge_lookup_member (struct bridge_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bridge_ioctl_gifflags(struct bridge_softc *sc, void *arg)
{
	struct ifbreq *req = arg;
	struct bridge_iflist *bif;

	bif = bridge_lookup_member(sc, req->ifbr_ifsname);
	if (bif == NULL)
		return (ENOENT);

	if (bridge_in_bsd_mode(sc)) {
		struct bstp_port *bp;

		bp = &bif->bif_stp;
		req->ifbr_state = bp->bp_state;
		req->ifbr_priority = bp->bp_priority;
		req->ifbr_path_cost = bp->bp_path_cost;
		req->ifbr_proto = bp->bp_protover;
		req->ifbr_role = bp->bp_role;
		req->ifbr_stpflags = bp->bp_flags;
		/* Copy STP state options as flags */
		if (bp->bp_operedge)
			req->ifbr_ifsflags |= IFBIF_BSTP_EDGE;
		if (bp->bp_flags & BSTP_PORT_AUTOEDGE)
			req->ifbr_ifsflags |= IFBIF_BSTP_AUTOEDGE;
		if (bp->bp_ptp_link)
			req->ifbr_ifsflags |= IFBIF_BSTP_PTP;
		if (bp->bp_flags & BSTP_PORT_AUTOPTP)
			req->ifbr_ifsflags |= IFBIF_BSTP_AUTOPTP;
		if (bp->bp_flags & BSTP_PORT_ADMEDGE)
			req->ifbr_ifsflags |= IFBIF_BSTP_ADMEDGE;
		if (bp->bp_flags & BSTP_PORT_ADMCOST)
			req->ifbr_ifsflags |= IFBIF_BSTP_ADMCOST;
	}
	req->ifbr_ifsflags = bif->bif_ifflags;
	req->ifbr_portno = bif->bif_ifp->if_index & 0xfff;
	req->ifbr_addrcnt = bif->bif_addrcnt;
	req->ifbr_addrmax = bif->bif_addrmax;
	req->ifbr_addrexceeded = bif->bif_addrexceeded;

	return (0);
}