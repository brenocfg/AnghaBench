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
typedef  int u8 ;
typedef  int u32 ;
struct r8192_priv {int bDynamicTxLowPower; scalar_t__ bIgnoreDiffRateTxPowerOffset; TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int scanning; } ;

/* Variables and functions */
 int RF6052_MAX_TX_PWR ; 
 int /*<<< orphan*/  bTxAGCRateCCK ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rTxAGC_CCK_Mcs32 ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

extern void PHY_RF6052SetCckTxPower(struct net_device* dev, u8	powerlevel)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	u32				TxAGC=0;

	if(priv->ieee80211->scanning == 1)
		TxAGC = 0x3f;
	else if(priv->bDynamicTxLowPower == true)//cosa 04282008 for cck long range
		TxAGC = 0x22;
	else
		TxAGC = powerlevel;

	//cosa add for lenovo, to pass the safety spec, don't increase power index for different rates.
	if(priv->bIgnoreDiffRateTxPowerOffset)
		TxAGC = powerlevel;

	if(TxAGC > RF6052_MAX_TX_PWR)
		TxAGC = RF6052_MAX_TX_PWR;

	//printk("CCK PWR= %x\n", TxAGC);
	rtl8192_setBBreg(dev, rTxAGC_CCK_Mcs32, bTxAGCRateCCK, TxAGC);

}