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
struct r8192_priv {int* TxPowerLevelCCK; int* TxPowerLevelOFDM24G; int rf_chip; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  Adapter ; 
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  PHY_SetRF8225CckTxPower (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PHY_SetRF8225OfdmTxPower (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PHY_SetRF8256CCKTxPower (struct net_device*,int) ; 
 int /*<<< orphan*/  PHY_SetRF8256OFDMTxPower (struct net_device*,int) ; 
#define  RF_8225 130 
#define  RF_8256 129 
#define  RF_8258 128 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

__attribute__((used)) static void rtl8192_SetTxPowerLevel(struct net_device *dev, u8 channel)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	u8	powerlevel = priv->TxPowerLevelCCK[channel-1];
	u8	powerlevelOFDM24G = priv->TxPowerLevelOFDM24G[channel-1];

	switch(priv->rf_chip)
	{
	case RF_8225:
#ifdef TO_DO_LIST
		PHY_SetRF8225CckTxPower(Adapter, powerlevel);
		PHY_SetRF8225OfdmTxPower(Adapter, powerlevelOFDM24G);
#endif
		break;

	case RF_8256:
		PHY_SetRF8256CCKTxPower(dev, powerlevel);
		PHY_SetRF8256OFDMTxPower(dev, powerlevelOFDM24G);
		break;

	case RF_8258:
		break;
	default:
		RT_TRACE(COMP_ERR, "unknown rf chip ID in rtl8192_SetTxPowerLevel()\n");
		break;
	}
	return;
}