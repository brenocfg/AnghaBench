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
typedef  int u32 ;
struct r8192_priv {TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IMR_BcnInt ; 
 int IMR_TBDER ; 
 int IMR_TBDOK ; 
 int /*<<< orphan*/  INTA_MASK ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int read_nic_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtl8192_beacon_disable(struct net_device *dev)
{
	struct r8192_priv *priv = (struct r8192_priv *)ieee80211_priv(dev);
	u32 reg;

	reg = read_nic_dword(priv->ieee80211->dev,INTA_MASK);

	/* disable Beacon realted interrupt signal */
	reg &= ~(IMR_BcnInt | IMR_BcnInt | IMR_TBDOK | IMR_TBDER);
	write_nic_dword(priv->ieee80211->dev, INTA_MASK, reg);
}