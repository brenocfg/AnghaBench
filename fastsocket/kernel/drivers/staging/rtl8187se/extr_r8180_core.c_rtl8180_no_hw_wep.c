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
struct r8180_priv {int /*<<< orphan*/  card_8185; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SECURITY ; 
 int SECURITY_WEP_RX_ENABLE_SHIFT ; 
 int SECURITY_WEP_TX_ENABLE_SHIFT ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 
 int read_nic_byte (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int) ; 

void rtl8180_no_hw_wep(struct net_device *dev)
{
	struct r8180_priv *priv = ieee80211_priv(dev);

	if (!priv->card_8185) {
		u8 security;

		security  = read_nic_byte(dev, SECURITY);
		security &=~(1<<SECURITY_WEP_TX_ENABLE_SHIFT);
		security &=~(1<<SECURITY_WEP_RX_ENABLE_SHIFT);

		write_nic_byte(dev, SECURITY, security);
	}
}