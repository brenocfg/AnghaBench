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
struct net_device {int tx_queue_len; int flags; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  mtu; scalar_t__ hard_header_len; int /*<<< orphan*/  type; int /*<<< orphan*/ * header_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_FDDI ; 
 int /*<<< orphan*/  FDDI_K_ALEN ; 
 int /*<<< orphan*/  FDDI_K_SNAP_DLEN ; 
 scalar_t__ FDDI_K_SNAP_HLEN ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int /*<<< orphan*/  fddi_header_ops ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fddi_setup(struct net_device *dev)
{
	dev->header_ops		= &fddi_header_ops;
	dev->type		= ARPHRD_FDDI;
	dev->hard_header_len	= FDDI_K_SNAP_HLEN+3;	/* Assume 802.2 SNAP hdr len + 3 pad bytes */
	dev->mtu		= FDDI_K_SNAP_DLEN;	/* Assume max payload of 802.2 SNAP frame */
	dev->addr_len		= FDDI_K_ALEN;
	dev->tx_queue_len	= 100;			/* Long queues on FDDI */
	dev->flags		= IFF_BROADCAST | IFF_MULTICAST;

	memset(dev->broadcast, 0xFF, FDDI_K_ALEN);
}