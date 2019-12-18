#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int /*<<< orphan*/  broadcast; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  mtu; } ;
struct TYPE_4__ {TYPE_1__* rom; } ;
struct hpsb_host {int node_count; int* speed; TYPE_2__ csr; } ;
struct eth1394_priv {int bc_maxpayload; int bc_sspd; int /*<<< orphan*/  lock; int /*<<< orphan*/  ud_list; struct hpsb_host* host; } ;
struct TYPE_3__ {int /*<<< orphan*/ * bus_info_data; } ;

/* Variables and functions */
 int IEEE1394_SPEED_100 ; 
 int IEEE1394_SPEED_MAX ; 
 int SELFID_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  ether1394_max_mtu (struct hpsb_host*) ; 
 int /*<<< orphan*/  get_unaligned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 
 struct eth1394_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ether1394_reset_priv(struct net_device *dev, int set_mtu)
{
	unsigned long flags;
	int i;
	struct eth1394_priv *priv = netdev_priv(dev);
	struct hpsb_host *host = priv->host;
	u64 guid = get_unaligned((u64 *)&(host->csr.rom->bus_info_data[3]));
	int max_speed = IEEE1394_SPEED_MAX;

	spin_lock_irqsave(&priv->lock, flags);

	memset(priv->ud_list, 0, sizeof(priv->ud_list));
	priv->bc_maxpayload = 512;

	/* Determine speed limit */
	/* FIXME: This is broken for nodes with link speed < PHY speed,
	 * and it is suboptimal for S200B...S800B hardware.
	 * The result of nodemgr's speed probe should be used somehow. */
	for (i = 0; i < host->node_count; i++) {
		/* take care of S100B...S400B PHY ports */
		if (host->speed[i] == SELFID_SPEED_UNKNOWN) {
			max_speed = IEEE1394_SPEED_100;
			break;
		}
		if (max_speed > host->speed[i])
			max_speed = host->speed[i];
	}
	priv->bc_sspd = max_speed;

	if (set_mtu) {
		/* Use the RFC 2734 default 1500 octets or the maximum payload
		 * as initial MTU */
		dev->mtu = min(1500, ether1394_max_mtu(host));

		/* Set our hardware address while we're at it */
		memcpy(dev->dev_addr, &guid, sizeof(u64));
		memset(dev->broadcast, 0xff, sizeof(u64));
	}

	spin_unlock_irqrestore(&priv->lock, flags);
}