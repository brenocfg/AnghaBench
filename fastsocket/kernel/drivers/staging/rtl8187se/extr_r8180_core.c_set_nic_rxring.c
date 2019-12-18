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
typedef  int u8 ;
struct r8180_priv {int /*<<< orphan*/  rxringdma; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PGSELECT ; 
 int PGSELECT_PG_SHIFT ; 
 int /*<<< orphan*/  RXRING_ADDR ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int read_nic_byte (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void set_nic_rxring(struct net_device *dev)
{
	u8 pgreg;
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);

	pgreg=read_nic_byte(dev, PGSELECT);
	write_nic_byte(dev, PGSELECT, pgreg &~ (1<<PGSELECT_PG_SHIFT));

	write_nic_dword(dev, RXRING_ADDR,priv->rxringdma);
}