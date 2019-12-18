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
struct net_device {int /*<<< orphan*/ * dev_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* copy_to_card ) (struct net_device*,int,int /*<<< orphan*/ ,struct arc_hardware*,int /*<<< orphan*/ ) ;} ;
struct arcnet_local {TYPE_1__ hw; } ;
struct archdr {int dummy; } ;
struct arc_hardware {int* offset; int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_HDR_SIZE ; 
 int /*<<< orphan*/  BUGMSG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  D_PROTO ; 
 struct arcnet_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int,int /*<<< orphan*/ ,struct arc_hardware*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int null_prepare_tx(struct net_device *dev, struct archdr *pkt,
			   int length, int bufnum)
{
	struct arcnet_local *lp = netdev_priv(dev);
	struct arc_hardware newpkt;

	BUGMSG(D_PROTO, "tx: no encap for this host; load a protocol driver.\n");

	/* send a packet to myself -- will never get received, of course */
	newpkt.source = newpkt.dest = dev->dev_addr[0];

	/* only one byte of actual data (and it's random) */
	newpkt.offset[0] = 0xFF;

	lp->hw.copy_to_card(dev, bufnum, 0, &newpkt, ARC_HDR_SIZE);

	return 1;		/* done */
}