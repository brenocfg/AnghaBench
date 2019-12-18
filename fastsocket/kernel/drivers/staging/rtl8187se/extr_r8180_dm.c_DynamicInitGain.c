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
struct r8180_priv {int rf_chip; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIG_Zebra (struct net_device*) ; 
#define  RF_ZEBRA2 129 
#define  RF_ZEBRA4 128 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int) ; 

void
DynamicInitGain(
	struct net_device *dev
	)
{
	struct r8180_priv *priv = ieee80211_priv(dev);

	switch(priv->rf_chip)
	{
		case RF_ZEBRA2:  // [AnnieWorkaround] For Zebra2, 2005-08-01.
		case RF_ZEBRA4:
			DIG_Zebra( dev );
			break;

		default:
			printk("DynamicInitGain(): unknown RFChipID(%d) !!!\n", priv->rf_chip);
			break;
	}
}