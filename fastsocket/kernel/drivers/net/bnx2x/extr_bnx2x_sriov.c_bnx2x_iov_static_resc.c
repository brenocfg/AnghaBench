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
typedef  int u16 ;
struct vf_pf_resc_request {int num_mac_filters; int num_vlan_filters; scalar_t__ num_mc_filters; scalar_t__ num_txqs; scalar_t__ num_rxqs; } ;
struct TYPE_2__ {int (* check ) (TYPE_1__*) ;} ;
struct bnx2x {TYPE_1__ vlans_pool; } ;

/* Variables and functions */
 int BNX2X_NR_VIRTFN (struct bnx2x*) ; 
 int ilog2 (int) ; 
 int stub1 (TYPE_1__*) ; 

__attribute__((used)) static void
bnx2x_iov_static_resc(struct bnx2x *bp, struct vf_pf_resc_request *resc)
{
	u16 vlan_count = 0;

	/* will be set only during VF-ACQUIRE */
	resc->num_rxqs = 0;
	resc->num_txqs = 0;

	/* no credit calculcis for macs (just yet) */
	resc->num_mac_filters = 1;

	/* divvy up vlan rules */
	vlan_count = bp->vlans_pool.check(&bp->vlans_pool);
	vlan_count = 1 << ilog2(vlan_count);
	resc->num_vlan_filters = vlan_count / BNX2X_NR_VIRTFN(bp);

	/* no real limitation */
	resc->num_mc_filters = 0;

	/* num_sbs already set */
}