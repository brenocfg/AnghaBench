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
struct net_device {int dummy; } ;
typedef  int WIRELESS_MODE ;

/* Variables and functions */
 scalar_t__ MAX_TXPWR_IDX_NMODE_92S ; 
#define  WIRELESS_MODE_B 130 
#define  WIRELESS_MODE_G 129 
#define  WIRELESS_MODE_N_24G 128 

__attribute__((used)) static u8 phy_DbmToTxPwrIdx(
	struct net_device* dev,
	WIRELESS_MODE	WirelessMode,
	long			PowerInDbm
	)
{
	//struct r8192_priv *priv = ieee80211_priv(dev);
	u8				TxPwrIdx = 0;
	long				Offset = 0;


	//
	// Tested by MP, we found that CCK Index 0 equals to -7dbm, OFDM legacy equals to
	// 3dbm, and OFDM HT equals to 0dbm repectively.
	// Note:
	//	The mapping may be different by different NICs. Do not use this formula for what needs accurate result.
	// By Bruce, 2008-01-29.
	//
	switch(WirelessMode)
	{
	case WIRELESS_MODE_B:
		Offset = -7;
		break;

	case WIRELESS_MODE_G:
	case WIRELESS_MODE_N_24G:
		Offset = -8;
		break;
	default:
		break;
	}

	if((PowerInDbm - Offset) > 0)
	{
		TxPwrIdx = (u8)((PowerInDbm - Offset) * 2);
	}
	else
	{
		TxPwrIdx = 0;
	}

	// Tx Power Index is too large.
	if(TxPwrIdx > MAX_TXPWR_IDX_NMODE_92S)
		TxPwrIdx = MAX_TXPWR_IDX_NMODE_92S;

	return TxPwrIdx;
}