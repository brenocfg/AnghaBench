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
typedef  int u16 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AtimWnd ; 
 int AtimWnd_AtimWnd ; 
 int /*<<< orphan*/  BintrItv ; 
 int BintrItv_BintrItv ; 
 int /*<<< orphan*/  DMESG (char*) ; 
 int /*<<< orphan*/  EPROM_CMD_NORMAL ; 
 int read_nic_word (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8180_beacon_tx_enable (struct net_device*) ; 
 int /*<<< orphan*/  rtl8180_irq_disable (struct net_device*) ; 
 int /*<<< orphan*/  rtl8180_prepare_beacon (struct net_device*) ; 
 int /*<<< orphan*/  rtl8180_set_mode (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8185b_irq_enable (struct net_device*) ; 
 int /*<<< orphan*/  write_nic_word (struct net_device*,int /*<<< orphan*/ ,int) ; 

void rtl8180_start_tx_beacon(struct net_device *dev)
{
	u16 word;

	DMESG("Enabling beacon TX");
	rtl8180_prepare_beacon(dev);
	rtl8180_irq_disable(dev);
	rtl8180_beacon_tx_enable(dev);

	word = read_nic_word(dev, AtimWnd) &~ AtimWnd_AtimWnd;
	write_nic_word(dev, AtimWnd,word);// word |=

	word  = read_nic_word(dev, BintrItv);
	word &= ~BintrItv_BintrItv;
	word |= 1000;/*priv->ieee80211->current_network.beacon_interval *
		((priv->txbeaconcount > 1)?(priv->txbeaconcount-1):1);
	// FIXME: check if correct ^^ worked with 0x3e8;
	*/
	write_nic_word(dev, BintrItv, word);

	rtl8180_set_mode(dev, EPROM_CMD_NORMAL);

        rtl8185b_irq_enable(dev);
}