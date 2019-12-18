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
typedef  int u32 ;
typedef  int u16 ;
struct r8192_priv {int short_preamble; int basic_rate; int nCur40MhzPrimeSC; int irq_mask; int ShortRetryLimit; int LongRetryLimit; struct ieee80211_device* ieee80211; } ;
struct net_device {int dummy; } ;
struct ieee80211_network {int capability; int beacon_interval; scalar_t__ bssid; } ;
struct ieee80211_device {scalar_t__ iw_mode; struct ieee80211_network current_network; } ;

/* Variables and functions */
 scalar_t__ BCN_INTERVAL ; 
 scalar_t__ BSSIDR ; 
 int IMR_BcnInt ; 
 int IMR_TBDER ; 
 int IMR_TBDOK ; 
 scalar_t__ INIRTSMCS_SEL ; 
 scalar_t__ IW_MODE_ADHOC ; 
 int /*<<< orphan*/  PHY_SetBeaconHwReg (struct net_device*,int) ; 
 scalar_t__ RETRY_LIMIT ; 
 int RETRY_LIMIT_LONG_SHIFT ; 
 int RETRY_LIMIT_SHORT_SHIFT ; 
 scalar_t__ RRSR ; 
 int WLAN_CAPABILITY_SHORT_PREAMBLE ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192_config_rate (struct net_device*,int*) ; 
 int /*<<< orphan*/  rtl8192_update_cap (struct net_device*,int) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  write_nic_word (struct net_device*,scalar_t__,int) ; 

void rtl8192SU_net_update(struct net_device *dev)
{

	struct r8192_priv *priv = ieee80211_priv(dev);
	struct ieee80211_device* ieee = priv->ieee80211;
	struct ieee80211_network *net = &priv->ieee80211->current_network;
	//u16 BcnTimeCfg = 0, BcnCW = 6, BcnIFS = 0xf;
	u16 rate_config = 0;
	u32 regTmp = 0;
	u8 rateIndex = 0;
	u8	retrylimit = 0x30;
	u16 cap = net->capability;

	priv->short_preamble = cap & WLAN_CAPABILITY_SHORT_PREAMBLE;

//HW_VAR_BASIC_RATE
	//update Basic rate: RR, BRSR
	rtl8192_config_rate(dev, &rate_config);	//HalSetBrateCfg

	priv->basic_rate = rate_config  = rate_config & 0x15f;

	// Set RRSR rate table.
	write_nic_byte(dev, RRSR, rate_config&0xff);
	write_nic_byte(dev, RRSR+1, (rate_config>>8)&0xff);

	// Set RTS initial rate
	while(rate_config > 0x1)
	{
		rate_config = (rate_config>> 1);
		rateIndex++;
	}
	write_nic_byte(dev, INIRTSMCS_SEL, rateIndex);
//HW_VAR_BASIC_RATE

	//set ack preample
	regTmp = (priv->nCur40MhzPrimeSC) << 5;
	if (priv->short_preamble)
		regTmp |= 0x80;
	write_nic_byte(dev, RRSR+2, regTmp);

	write_nic_dword(dev,BSSIDR,((u32*)net->bssid)[0]);
	write_nic_word(dev,BSSIDR+4,((u16*)net->bssid)[2]);

	write_nic_word(dev, BCN_INTERVAL, net->beacon_interval);
	//2008.10.24 added by tynli for beacon changed.
	PHY_SetBeaconHwReg( dev, net->beacon_interval);

	rtl8192_update_cap(dev, cap);

	if (ieee->iw_mode == IW_MODE_ADHOC){
		retrylimit = 7;
		//we should enable ibss interrupt here, but disable it temporarily
		if (0){
			priv->irq_mask |= (IMR_BcnInt | IMR_BcnInt | IMR_TBDOK | IMR_TBDER);
			//rtl8192_irq_disable(dev);
			//rtl8192_irq_enable(dev);
		}
	}
	else{
		if (0){
			priv->irq_mask &= ~(IMR_BcnInt | IMR_BcnInt | IMR_TBDOK | IMR_TBDER);
			//rtl8192_irq_disable(dev);
			//rtl8192_irq_enable(dev);
		}
	}

	priv->ShortRetryLimit = priv->LongRetryLimit = retrylimit;

	write_nic_word(dev, 	RETRY_LIMIT,
				retrylimit << RETRY_LIMIT_SHORT_SHIFT | \
				retrylimit << RETRY_LIMIT_LONG_SHIFT);
}