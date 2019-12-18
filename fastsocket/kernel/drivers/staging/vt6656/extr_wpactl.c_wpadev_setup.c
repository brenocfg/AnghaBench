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
struct net_device {int mtu; int tx_queue_len; int flags; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  hard_header_len; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_IEEE80211 ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wpadev_setup(struct net_device *dev)
{
	dev->type               = ARPHRD_IEEE80211;
	dev->hard_header_len    = ETH_HLEN;
	dev->mtu                = 2048;
	dev->addr_len           = ETH_ALEN;
	dev->tx_queue_len       = 1000;

	memset(dev->broadcast,0xFF, ETH_ALEN);

	dev->flags              = IFF_BROADCAST|IFF_MULTICAST;
}