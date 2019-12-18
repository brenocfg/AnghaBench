#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct r8192_priv {scalar_t__ CCKPresentAttentuation; TYPE_2__* cck_txbbgain_ch14_table; TYPE_1__* cck_txbbgain_table; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int* ccktxbb_valuearray; } ;
struct TYPE_3__ {int* ccktxbb_valuearray; } ;

/* Variables and functions */
 int /*<<< orphan*/  bMaskDWord ; 
 int /*<<< orphan*/  bMaskHWord ; 
 int /*<<< orphan*/  bMaskLWord ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rCCK0_DebugPort ; 
 int /*<<< orphan*/  rCCK0_TxFilter1 ; 
 int /*<<< orphan*/  rCCK0_TxFilter2 ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void dm_CCKTxPowerAdjust_TSSI(struct net_device *dev, bool  bInCH14)
{
	u32 TempVal;
	struct r8192_priv *priv = ieee80211_priv(dev);
	//Write 0xa22 0xa23
	TempVal = 0;
	if(!bInCH14){
		//Write 0xa22 0xa23
		TempVal = 	(u32)(priv->cck_txbbgain_table[(u8)(priv->CCKPresentAttentuation)].ccktxbb_valuearray[0] +
					(priv->cck_txbbgain_table[(u8)(priv->CCKPresentAttentuation)].ccktxbb_valuearray[1]<<8)) ;

		rtl8192_setBBreg(dev, rCCK0_TxFilter1,bMaskHWord, TempVal);
		//Write 0xa24 ~ 0xa27
		TempVal = 0;
		TempVal = 	(u32)(priv->cck_txbbgain_table[(u8)(priv->CCKPresentAttentuation)].ccktxbb_valuearray[2] +
					(priv->cck_txbbgain_table[(u8)(priv->CCKPresentAttentuation)].ccktxbb_valuearray[3]<<8) +
					(priv->cck_txbbgain_table[(u8)(priv->CCKPresentAttentuation)].ccktxbb_valuearray[4]<<16 )+
					(priv->cck_txbbgain_table[(u8)(priv->CCKPresentAttentuation)].ccktxbb_valuearray[5]<<24));
		rtl8192_setBBreg(dev, rCCK0_TxFilter2,bMaskDWord, TempVal);
		//Write 0xa28  0xa29
		TempVal = 0;
		TempVal = 	(u32)(priv->cck_txbbgain_table[(u8)(priv->CCKPresentAttentuation)].ccktxbb_valuearray[6] +
					(priv->cck_txbbgain_table[(u8)(priv->CCKPresentAttentuation)].ccktxbb_valuearray[7]<<8)) ;

		rtl8192_setBBreg(dev, rCCK0_DebugPort,bMaskLWord, TempVal);
	}
	else
	{
		TempVal = 	(u32)(priv->cck_txbbgain_ch14_table[(u8)(priv->CCKPresentAttentuation)].ccktxbb_valuearray[0] +
					(priv->cck_txbbgain_ch14_table[(u8)(priv->CCKPresentAttentuation)].ccktxbb_valuearray[1]<<8)) ;

		rtl8192_setBBreg(dev, rCCK0_TxFilter1,bMaskHWord, TempVal);
		//Write 0xa24 ~ 0xa27
		TempVal = 0;
		TempVal = 	(u32)(priv->cck_txbbgain_ch14_table[(u8)(priv->CCKPresentAttentuation)].ccktxbb_valuearray[2] +
					(priv->cck_txbbgain_ch14_table[(u8)(priv->CCKPresentAttentuation)].ccktxbb_valuearray[3]<<8) +
					(priv->cck_txbbgain_ch14_table[(u8)(priv->CCKPresentAttentuation)].ccktxbb_valuearray[4]<<16 )+
					(priv->cck_txbbgain_ch14_table[(u8)(priv->CCKPresentAttentuation)].ccktxbb_valuearray[5]<<24));
		rtl8192_setBBreg(dev, rCCK0_TxFilter2,bMaskDWord, TempVal);
		//Write 0xa28  0xa29
		TempVal = 0;
		TempVal = 	(u32)(priv->cck_txbbgain_ch14_table[(u8)(priv->CCKPresentAttentuation)].ccktxbb_valuearray[6] +
					(priv->cck_txbbgain_ch14_table[(u8)(priv->CCKPresentAttentuation)].ccktxbb_valuearray[7]<<8)) ;

		rtl8192_setBBreg(dev, rCCK0_DebugPort,bMaskLWord, TempVal);
	}


}