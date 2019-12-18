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
struct net_device {int hard_header_len; int tx_queue_len; int* broadcast; int /*<<< orphan*/  flags; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  mtu; int /*<<< orphan*/ * header_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  type; } ;
struct archdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCNET_ALEN ; 
 int /*<<< orphan*/  ARPHRD_ARCNET ; 
 int /*<<< orphan*/  IFF_BROADCAST ; 
 int /*<<< orphan*/  TX_TIMEOUT ; 
 int /*<<< orphan*/  arcnet_header_ops ; 
 int /*<<< orphan*/  arcnet_netdev_ops ; 
 int /*<<< orphan*/  choose_mtu () ; 

__attribute__((used)) static void arcdev_setup(struct net_device *dev)
{
	dev->type = ARPHRD_ARCNET;
	dev->netdev_ops = &arcnet_netdev_ops;
	dev->header_ops = &arcnet_header_ops;
	dev->hard_header_len = sizeof(struct archdr);
	dev->mtu = choose_mtu();

	dev->addr_len = ARCNET_ALEN;
	dev->tx_queue_len = 100;
	dev->broadcast[0] = 0x00;	/* for us, broadcasts are address 0 */
	dev->watchdog_timeo = TX_TIMEOUT;

	/* New-style flags. */
	dev->flags = IFF_BROADCAST;

}