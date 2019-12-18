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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* copy_to_card ) (struct net_device*,int,int,struct arc_hardware*,int) ;} ;
struct arcnet_local {int /*<<< orphan*/  lastload_dest; TYPE_1__ hw; int /*<<< orphan*/  cur_tx; int /*<<< orphan*/  next_tx; } ;
struct arc_hardware {int* offset; int /*<<< orphan*/  dest; } ;
struct archdr {struct arc_hardware soft; struct arc_hardware hard; } ;

/* Variables and functions */
 int ARC_HDR_SIZE ; 
 int /*<<< orphan*/  BUGMSG (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  D_DURING ; 
 int /*<<< orphan*/  D_NORMAL ; 
 int MTU ; 
 int MinTU ; 
 int XMTU ; 
 struct arcnet_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int,int,struct arc_hardware*,int) ; 
 int /*<<< orphan*/  stub2 (struct net_device*,int,int,struct arc_hardware*,int) ; 

__attribute__((used)) static int prepare_tx(struct net_device *dev, struct archdr *pkt, int length,
		      int bufnum)
{
	struct arcnet_local *lp = netdev_priv(dev);
	struct arc_hardware *hard = &pkt->hard;
	int ofs;

	BUGMSG(D_DURING, "prepare_tx: txbufs=%d/%d/%d\n",
	       lp->next_tx, lp->cur_tx, bufnum);

	length -= ARC_HDR_SIZE;	/* hard header is not included in packet length */

	if (length > XMTU) {
		/* should never happen! other people already check for this. */
		BUGMSG(D_NORMAL, "Bug!  prepare_tx with size %d (> %d)\n",
		       length, XMTU);
		length = XMTU;
	}
	if (length >= MinTU) {
		hard->offset[0] = 0;
		hard->offset[1] = ofs = 512 - length;
	} else if (length > MTU) {
		hard->offset[0] = 0;
		hard->offset[1] = ofs = 512 - length - 3;
	} else
		hard->offset[0] = ofs = 256 - length;

	BUGMSG(D_DURING, "prepare_tx: length=%d ofs=%d\n",
	       length,ofs);

	lp->hw.copy_to_card(dev, bufnum, 0, hard, ARC_HDR_SIZE);
	lp->hw.copy_to_card(dev, bufnum, ofs, &pkt->soft, length);

	lp->lastload_dest = hard->dest;

	return 1;		/* done */
}