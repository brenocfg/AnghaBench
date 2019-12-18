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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct r8180_priv {int RegHiPwrUpperTh; int RegHiPwrLowerTh; scalar_t__ RegRSSIHiPwrUpperTh; scalar_t__ RegRSSIHiPwrLowerTh; char* chtxpwr_ofdm; char* chtxpwr; int UndecoratedSmoothedSS; scalar_t__ CurCCKRSSI; int bToUpdateTxPwr; scalar_t__ bCurCCKPkt; TYPE_2__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {size_t channel; } ;
struct TYPE_4__ {TYPE_1__ current_network; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCK_TXAGC ; 
 int /*<<< orphan*/  OFDM_TXAGC ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 
 scalar_t__ read_nic_byte (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,char) ; 

void
DoTxHighPower(
	struct net_device *dev
	)
{
	struct r8180_priv *priv = ieee80211_priv(dev);
	u16			HiPwrUpperTh = 0;
	u16			HiPwrLowerTh = 0;
	u8			RSSIHiPwrUpperTh;
	u8			RSSIHiPwrLowerTh;
	u8			u1bTmp;
	char			OfdmTxPwrIdx, CckTxPwrIdx;

	//printk("----> DoTxHighPower()\n");

	HiPwrUpperTh = priv->RegHiPwrUpperTh;
	HiPwrLowerTh = priv->RegHiPwrLowerTh;

	HiPwrUpperTh = HiPwrUpperTh * 10;
	HiPwrLowerTh = HiPwrLowerTh * 10;
	RSSIHiPwrUpperTh = priv->RegRSSIHiPwrUpperTh;
	RSSIHiPwrLowerTh = priv->RegRSSIHiPwrLowerTh;

	//lzm add 080826
	OfdmTxPwrIdx  = priv->chtxpwr_ofdm[priv->ieee80211->current_network.channel];
	CckTxPwrIdx  = priv->chtxpwr[priv->ieee80211->current_network.channel];

	//	printk("DoTxHighPower() - UndecoratedSmoothedSS:%d, CurCCKRSSI = %d , bCurCCKPkt= %d \n", priv->UndecoratedSmoothedSS, priv->CurCCKRSSI, priv->bCurCCKPkt );

	if((priv->UndecoratedSmoothedSS > HiPwrUpperTh) ||
		(priv->bCurCCKPkt && (priv->CurCCKRSSI > RSSIHiPwrUpperTh)))
	{
		// Stevenl suggested that degrade 8dbm in high power sate. 2007-12-04 Isaiah

	//	printk("=====>DoTxHighPower() - High Power - UndecoratedSmoothedSS:%d,  HiPwrUpperTh = %d \n", priv->UndecoratedSmoothedSS, HiPwrUpperTh );
		priv->bToUpdateTxPwr = true;
		u1bTmp= read_nic_byte(dev, CCK_TXAGC);

		// If it never enter High Power.
		if( CckTxPwrIdx == u1bTmp)
		{
		u1bTmp = (u1bTmp > 16) ? (u1bTmp -16): 0;  // 8dbm
		write_nic_byte(dev, CCK_TXAGC, u1bTmp);

		u1bTmp= read_nic_byte(dev, OFDM_TXAGC);
		u1bTmp = (u1bTmp > 16) ? (u1bTmp -16): 0;  // 8dbm
		write_nic_byte(dev, OFDM_TXAGC, u1bTmp);
		}

	}
	else if((priv->UndecoratedSmoothedSS < HiPwrLowerTh) &&
		(!priv->bCurCCKPkt || priv->CurCCKRSSI < RSSIHiPwrLowerTh))
	{
	//	 printk("DoTxHighPower() - lower Power - UndecoratedSmoothedSS:%d,  HiPwrUpperTh = %d \n", priv->UndecoratedSmoothedSS, HiPwrLowerTh );
		if(priv->bToUpdateTxPwr)
		{
			priv->bToUpdateTxPwr = false;
			//SD3 required.
			u1bTmp= read_nic_byte(dev, CCK_TXAGC);
			if(u1bTmp < CckTxPwrIdx)
			{
			//u1bTmp = ((u1bTmp+16) > 35) ? 35: (u1bTmp+16);  // 8dbm
			//write_nic_byte(dev, CCK_TXAGC, u1bTmp);
			write_nic_byte(dev, CCK_TXAGC, CckTxPwrIdx);
			}

			u1bTmp= read_nic_byte(dev, OFDM_TXAGC);
			if(u1bTmp < OfdmTxPwrIdx)
			{
			//u1bTmp = ((u1bTmp+16) > 35) ? 35: (u1bTmp+16);  // 8dbm
			//write_nic_byte(dev, OFDM_TXAGC, u1bTmp);
			write_nic_byte(dev, OFDM_TXAGC, OfdmTxPwrIdx);
			}
		}
	}

	//printk("<---- DoTxHighPower()\n");
}