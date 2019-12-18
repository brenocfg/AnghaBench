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
struct r8180_priv {int /*<<< orphan*/  TransmitConfig; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 int CMD_TX_ENABLE_SHIFT ; 
 int /*<<< orphan*/  DMESG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSR ; 
 int MSR_LINK_ENEDCA ; 
 int /*<<< orphan*/  TCR ; 
 int /*<<< orphan*/  fix_tx_fifo (struct net_device*) ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int read_nic_byte (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_nic_dword (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtl8185b_tx_enable(struct net_device *dev)
{
	u8 cmd;
	//u8 tx_agc_ctl;
	u8 byte;
	//u32 txconf;
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);

	write_nic_dword(dev, TCR, priv->TransmitConfig);
	byte = read_nic_byte(dev, MSR);
	byte |= MSR_LINK_ENEDCA;
	write_nic_byte(dev, MSR, byte);

	fix_tx_fifo(dev);

#ifdef DEBUG_TX
	DMESG("txconf: %x %x",priv->TransmitConfig,read_nic_dword(dev,TCR));
#endif

	cmd=read_nic_byte(dev,CMD);
	write_nic_byte(dev,CMD,cmd | (1<<CMD_TX_ENABLE_SHIFT));

	//write_nic_dword(dev,TX_CONF,txconf);


/*
	rtl8180_set_mode(dev,EPROM_CMD_CONFIG);
	write_nic_byte(dev, TX_DMA_POLLING, priv->dma_poll_mask);
	rtl8180_set_mode(dev,EPROM_CMD_NORMAL);
	*/
}