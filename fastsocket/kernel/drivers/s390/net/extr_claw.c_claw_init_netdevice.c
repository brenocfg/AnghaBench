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
struct net_device {int tx_queue_len; int flags; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  type; scalar_t__ addr_len; scalar_t__ hard_header_len; int /*<<< orphan*/  mtu; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_SLIP ; 
 int /*<<< orphan*/  CLAW_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CLAW_DBF_TEXT_ (int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLAW_DEFAULT_MTU_SIZE ; 
 int IFF_NOARP ; 
 int IFF_POINTOPOINT ; 
 int /*<<< orphan*/  claw_netdev_ops ; 
 int /*<<< orphan*/  setup ; 

__attribute__((used)) static void
claw_init_netdevice(struct net_device * dev)
{
	CLAW_DBF_TEXT(2, setup, "init_dev");
	CLAW_DBF_TEXT_(2, setup, "%s", dev->name);
	dev->mtu = CLAW_DEFAULT_MTU_SIZE;
	dev->hard_header_len = 0;
	dev->addr_len = 0;
	dev->type = ARPHRD_SLIP;
	dev->tx_queue_len = 1300;
	dev->flags = IFF_POINTOPOINT | IFF_NOARP;
	dev->netdev_ops = &claw_netdev_ops;
	CLAW_DBF_TEXT(2, setup, "initok");
	return;
}