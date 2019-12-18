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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtl8192_rx_initiate (struct net_device*) ; 

void rtl8192_rx_enable(struct net_device *dev)
{
	//u8 cmd;

	//struct r8192_priv *priv = (struct r8192_priv *)ieee80211_priv(dev);

	rtl8192_rx_initiate(dev);

//	rtl8192_set_rxconf(dev);
}