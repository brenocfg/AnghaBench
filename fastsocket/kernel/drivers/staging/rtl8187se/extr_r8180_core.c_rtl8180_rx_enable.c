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
struct r8180_priv {scalar_t__ card_8185; int crcmon; int rcr_csense; TYPE_1__* ieee80211; } ;
struct net_device {int flags; } ;
struct TYPE_2__ {scalar_t__ iw_mode; } ;

/* Variables and functions */
 int ACCEPT_ALLMAC_FRAME_SHIFT ; 
 int ACCEPT_BCAST_FRAME_SHIFT ; 
 int ACCEPT_CRCERR_FRAME_SHIFT ; 
 int ACCEPT_CTL_FRAME_SHIFT ; 
 int ACCEPT_DATA_FRAME_SHIFT ; 
 int ACCEPT_ICVERR_FRAME_SHIFT ; 
 int ACCEPT_MCAST_FRAME_SHIFT ; 
 int ACCEPT_MNG_FRAME_SHIFT ; 
 int ACCEPT_NICMAC_FRAME_SHIFT ; 
 int ACCEPT_PWR_FRAME_SHIFT ; 
 int /*<<< orphan*/  CMD ; 
 int CMD_RX_ENABLE_SHIFT ; 
 int /*<<< orphan*/  DMESG (char*) ; 
 int IFF_PROMISC ; 
 scalar_t__ IW_MODE_MONITOR ; 
 int MAC_FILTER_MASK ; 
 int MAX_RX_DMA_2048 ; 
 int MAX_RX_DMA_MASK ; 
 int MAX_RX_DMA_SHIFT ; 
 int RCR_CS_MASK ; 
 int RCR_CS_SHIFT ; 
 int RCR_ONLYERLPKT ; 
 int RX_AUTORESETPHY_SHIFT ; 
 int RX_CHECK_BSSID_SHIFT ; 
 int /*<<< orphan*/  RX_CONF ; 
 int RX_FIFO_THRESHOLD_MASK ; 
 int RX_FIFO_THRESHOLD_NONE ; 
 int RX_FIFO_THRESHOLD_SHIFT ; 
 int /*<<< orphan*/  fix_rx_fifo (struct net_device*) ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int read_nic_byte (struct net_device*,int /*<<< orphan*/ ) ; 
 int read_nic_dword (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int /*<<< orphan*/ ,int) ; 

void rtl8180_rx_enable(struct net_device *dev)
{
	u8 cmd;
	u32 rxconf;
	/* for now we accept data, management & ctl frame*/
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);

	rxconf=read_nic_dword(dev,RX_CONF);
	rxconf = rxconf &~ MAC_FILTER_MASK;
	rxconf = rxconf | (1<<ACCEPT_MNG_FRAME_SHIFT);
	rxconf = rxconf | (1<<ACCEPT_DATA_FRAME_SHIFT);
	rxconf = rxconf | (1<<ACCEPT_BCAST_FRAME_SHIFT);
	rxconf = rxconf | (1<<ACCEPT_MCAST_FRAME_SHIFT);
	if (dev->flags & IFF_PROMISC)
		DMESG("NIC in promisc mode");

	if(priv->ieee80211->iw_mode == IW_MODE_MONITOR || \
	   dev->flags & IFF_PROMISC){
		rxconf = rxconf | (1<<ACCEPT_ALLMAC_FRAME_SHIFT);
	}else{
		rxconf = rxconf | (1<<ACCEPT_NICMAC_FRAME_SHIFT);
		if(priv->card_8185 == 0)
			rxconf = rxconf | (1<<RX_CHECK_BSSID_SHIFT);
	}

	if(priv->ieee80211->iw_mode == IW_MODE_MONITOR){
		rxconf = rxconf | (1<<ACCEPT_CTL_FRAME_SHIFT);
		rxconf = rxconf | (1<<ACCEPT_ICVERR_FRAME_SHIFT);
		rxconf = rxconf | (1<<ACCEPT_PWR_FRAME_SHIFT);
	}

	if( priv->crcmon == 1 && priv->ieee80211->iw_mode == IW_MODE_MONITOR)
		rxconf = rxconf | (1<<ACCEPT_CRCERR_FRAME_SHIFT);

	rxconf = rxconf & ~RX_FIFO_THRESHOLD_MASK;
	rxconf = rxconf | (RX_FIFO_THRESHOLD_NONE << RX_FIFO_THRESHOLD_SHIFT);

	rxconf = rxconf | (1<<RX_AUTORESETPHY_SHIFT);
	rxconf = rxconf &~ MAX_RX_DMA_MASK;
	rxconf = rxconf | (MAX_RX_DMA_2048<<MAX_RX_DMA_SHIFT);

	rxconf = rxconf | RCR_ONLYERLPKT;

	rxconf = rxconf &~ RCR_CS_MASK;

	if (!priv->card_8185)
		rxconf |= (priv->rcr_csense<<RCR_CS_SHIFT);

	write_nic_dword(dev, RX_CONF, rxconf);

	fix_rx_fifo(dev);

	cmd=read_nic_byte(dev,CMD);
	write_nic_byte(dev,CMD,cmd | (1<<CMD_RX_ENABLE_SHIFT));
}