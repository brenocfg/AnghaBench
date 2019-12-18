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
typedef  scalar_t__ u8 ;
struct r8192_priv {scalar_t__ CurrentOfdm24GTxPwrIdx; scalar_t__ LegacyHTTxPowerDiff; scalar_t__ CurrentCckTxPwrIdx; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIRELESS_MODE_B ; 
 int /*<<< orphan*/  WIRELESS_MODE_G ; 
 int /*<<< orphan*/  WIRELESS_MODE_N_24G ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 long phy_TxPwrIdxToDbm (struct net_device*,int /*<<< orphan*/ ,scalar_t__) ; 

void
PHY_GetTxPowerLevel8192S(
	struct net_device* dev,
	 long*    		powerlevel
	)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	u8			TxPwrLevel = 0;
	long			TxPwrDbm;
	//
	// Because the Tx power indexes are different, we report the maximum of them to
	// meet the CCX TPC request. By Bruce, 2008-01-31.
	//

	// CCK
	TxPwrLevel = priv->CurrentCckTxPwrIdx;
	TxPwrDbm = phy_TxPwrIdxToDbm(dev, WIRELESS_MODE_B, TxPwrLevel);

	// Legacy OFDM
	TxPwrLevel = priv->CurrentOfdm24GTxPwrIdx + priv->LegacyHTTxPowerDiff;

	// Compare with Legacy OFDM Tx power.
	if(phy_TxPwrIdxToDbm(dev, WIRELESS_MODE_G, TxPwrLevel) > TxPwrDbm)
		TxPwrDbm = phy_TxPwrIdxToDbm(dev, WIRELESS_MODE_G, TxPwrLevel);

	// HT OFDM
	TxPwrLevel = priv->CurrentOfdm24GTxPwrIdx;

	// Compare with HT OFDM Tx power.
	if(phy_TxPwrIdxToDbm(dev, WIRELESS_MODE_N_24G, TxPwrLevel) > TxPwrDbm)
		TxPwrDbm = phy_TxPwrIdxToDbm(dev, WIRELESS_MODE_N_24G, TxPwrLevel);

	*powerlevel = TxPwrDbm;
}