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
struct r8180_priv {scalar_t__ card_8185; } ;
typedef  int s8 ;
typedef  int s32 ;
typedef  scalar_t__ WIRELESS_MODE ;

/* Variables and functions */
 scalar_t__ VERSION_8187S_B ; 
 scalar_t__ WIRELESS_MODE_B ; 
 scalar_t__ WIRELESS_MODE_G ; 

s8 DbmToTxPwrIdx(struct r8180_priv *priv, WIRELESS_MODE WirelessMode,
		 s32 PowerInDbm)
{
 	bool bUseDefault = true;
	s8 TxPwrIdx = 0;

	/*
	 * OFDM Power in dBm = Index * 0.5 + 0
	 * CCK Power in dBm = Index * 0.25 + 13
	 */
	if (priv->card_8185 >= VERSION_8187S_B) {
		s32 tmp = 0;

		if (WirelessMode == WIRELESS_MODE_G) {
			bUseDefault = false;
			tmp = (2 * PowerInDbm);

			if (tmp < 0)
				TxPwrIdx = 0;
			else if (tmp > 40) /* 40 means 20 dBm. */
				TxPwrIdx = 40;
			else
				TxPwrIdx = (s8)tmp;
		} else if (WirelessMode == WIRELESS_MODE_B) {
			bUseDefault = false;
			tmp = (4 * PowerInDbm) - 52;

			if(tmp < 0)
				TxPwrIdx = 0;
			else if (tmp > 28) /* 28 means 20 dBm. */
				TxPwrIdx = 28;
			else
				TxPwrIdx = (s8)tmp;
		}
	}

	/*
	 * TRUE if we want to use a default implementation.
	 * We shall set it to FALSE when we have exact translation formular
	 * for target IC. 070622, by rcnjko.
	 */
	if (bUseDefault) {
		if (PowerInDbm < 0)
			TxPwrIdx = 0;
		else if (PowerInDbm > 35)
			TxPwrIdx = 35;
		else
			TxPwrIdx = (u8)PowerInDbm;
	}

	return TxPwrIdx;
}