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
struct net_device {int mtu; int tx_queue_len; int flags; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  hard_header_len; int /*<<< orphan*/  type; int /*<<< orphan*/ * header_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_IEEE802_TR ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int /*<<< orphan*/  TR_ALEN ; 
 int /*<<< orphan*/  TR_HLEN ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tr_header_ops ; 

__attribute__((used)) static void tr_setup(struct net_device *dev)
{
	/*
	 *	Configure and register
	 */

	dev->header_ops	= &tr_header_ops;

	dev->type		= ARPHRD_IEEE802_TR;
	dev->hard_header_len	= TR_HLEN;
	dev->mtu		= 2000;
	dev->addr_len		= TR_ALEN;
	dev->tx_queue_len	= 100;	/* Long queues on tr */

	memset(dev->broadcast,0xFF, TR_ALEN);

	/* New-style flags. */
	dev->flags		= IFF_BROADCAST | IFF_MULTICAST ;
}