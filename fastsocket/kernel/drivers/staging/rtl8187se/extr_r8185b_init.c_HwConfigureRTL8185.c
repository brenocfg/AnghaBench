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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANTSEL ; 
 int /*<<< orphan*/  ARFR ; 
 int /*<<< orphan*/  BRSR ; 
 int /*<<< orphan*/  CCK_TXAGC ; 
 int /*<<< orphan*/  CW_CONF ; 
 int /*<<< orphan*/  OFDM_TXAGC ; 
 int /*<<< orphan*/  PlatformIOWrite2Byte (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RATE_FALLBACK ; 
 int RATE_FALLBACK_CTL_AUTO_STEP1 ; 
 int RATE_FALLBACK_CTL_ENABLE ; 
 int /*<<< orphan*/  TXAGC_CTL ; 
 int read_nic_byte (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_nic_word (struct net_device*,int /*<<< orphan*/ ,int) ; 

void
HwConfigureRTL8185(
		struct net_device *dev
		)
{
	//RTL8185_TODO: Determine Retrylimit, TxAGC, AutoRateFallback control.
//	u8		bUNIVERSAL_CONTROL_RL = 1;
        u8              bUNIVERSAL_CONTROL_RL = 0;

	u8		bUNIVERSAL_CONTROL_AGC = 1;
	u8		bUNIVERSAL_CONTROL_ANT = 1;
	u8		bAUTO_RATE_FALLBACK_CTL = 1;
	u8		val8;
	//struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);
	//struct ieee80211_device *ieee = priv->ieee80211;
      	//if(IS_WIRELESS_MODE_A(dev) || IS_WIRELESS_MODE_G(dev))
//{by amy 080312	if((ieee->mode == IEEE_G)||(ieee->mode == IEEE_A))
//	{
//		write_nic_word(dev, BRSR, 0xffff);
//	}
//	else
//	{
//		write_nic_word(dev, BRSR, 0x000f);
//	}
//by amy 080312}
        write_nic_word(dev, BRSR, 0x0fff);
	// Retry limit
	val8 = read_nic_byte(dev, CW_CONF);

	if(bUNIVERSAL_CONTROL_RL)
		val8 = val8 & 0xfd;
	else
		val8 = val8 | 0x02;

	write_nic_byte(dev, CW_CONF, val8);

	// Tx AGC
	val8 = read_nic_byte(dev, TXAGC_CTL);
	if(bUNIVERSAL_CONTROL_AGC)
	{
		write_nic_byte(dev, CCK_TXAGC, 128);
		write_nic_byte(dev, OFDM_TXAGC, 128);
		val8 = val8 & 0xfe;
	}
	else
	{
		val8 = val8 | 0x01 ;
	}


	write_nic_byte(dev, TXAGC_CTL, val8);

	// Tx Antenna including Feedback control
	val8 = read_nic_byte(dev, TXAGC_CTL );

	if(bUNIVERSAL_CONTROL_ANT)
	{
		write_nic_byte(dev, ANTSEL, 0x00);
		val8 = val8 & 0xfd;
	}
	else
	{
		val8 = val8 & (val8|0x02); //xiong-2006-11-15
	}

	write_nic_byte(dev, TXAGC_CTL, val8);

	// Auto Rate fallback control
	val8 = read_nic_byte(dev, RATE_FALLBACK);
	val8 &= 0x7c;
	if( bAUTO_RATE_FALLBACK_CTL )
	{
		val8 |= RATE_FALLBACK_CTL_ENABLE | RATE_FALLBACK_CTL_AUTO_STEP1;

		// <RJ_TODO_8185B> We shall set up the ARFR according to user's setting.
		//write_nic_word(dev, ARFR, 0x0fff); // set 1M ~ 54M
//by amy
	        // Aadded by Roger, 2007.11.15.
	        PlatformIOWrite2Byte(dev, ARFR, 0x0fff); //set 1M ~ 54Mbps.
//by amy
	}
	else
	{
	}
	write_nic_byte(dev, RATE_FALLBACK, val8);
}