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
typedef  int u16 ;
struct r8192_priv {scalar_t__ LoopbackMode; scalar_t__ bBootFromEfuse; int /*<<< orphan*/  ReceiveConfig; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int BBRSTn ; 
 int BB_GLB_RSTn ; 
 int BIT7 ; 
 int /*<<< orphan*/  CMDR ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int DDMA_EN ; 
 scalar_t__ EFUSE_CTRL ; 
 int FW2HW_EN ; 
 int HCI_RXDMA_EN ; 
 int HCI_TXDMA_EN ; 
 scalar_t__ LBKMD_SEL ; 
 int LBK_MAC_DLB ; 
 int LBK_NORMAL ; 
 int MACRXEN ; 
 int MACTXEN ; 
 int /*<<< orphan*/  RCR ; 
 scalar_t__ RTL8192SU_MAC_LOOPBACK ; 
 scalar_t__ RTL8192SU_NO_LOOPBACK ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,...) ; 
 int RXDMA_EN ; 
 int SCHEDULE_EN ; 
 scalar_t__ SYS_ISO_CTRL ; 
 int TXDMA_EN ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int read_nic_byte (struct net_device*,scalar_t__) ; 
 int read_nic_byte_E (struct net_device*,int) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  write_nic_byte_E (struct net_device*,int,int) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_word (struct net_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtl8192SU_MacConfigAfterFwDownload(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv((struct net_device *)dev);
	//PRT_HIGH_THROUGHPUT	pHTInfo = priv->ieee80211->pHTInfo;
	//u8	tmpU1b, RxPageCfg, i;
	u16	tmpU2b;
	u8	tmpU1b;//, i;


	RT_TRACE(COMP_INIT, "--->MacConfigAfterFwDownload()\n");

	// Enable Tx/Rx
	tmpU2b = (BBRSTn|BB_GLB_RSTn|SCHEDULE_EN|MACRXEN|MACTXEN|DDMA_EN|
			 FW2HW_EN|RXDMA_EN|TXDMA_EN|HCI_RXDMA_EN|HCI_TXDMA_EN);		//3
	//Adapter->HalFunc.SetHwRegHandler( Adapter, HW_VAR_COMMAND, &tmpU1b );
	write_nic_word(dev, CMDR, tmpU2b); //LZM REGISTER COM 090305

	// Loopback mode or not
	priv->LoopbackMode = RTL8192SU_NO_LOOPBACK; // Set no loopback as default.
	if(priv->LoopbackMode == RTL8192SU_NO_LOOPBACK)
		tmpU1b = LBK_NORMAL;
	else if (priv->LoopbackMode == RTL8192SU_MAC_LOOPBACK )
		tmpU1b = LBK_MAC_DLB;
	else
		RT_TRACE(COMP_INIT, "Serious error: wrong loopback mode setting\n");

	//Adapter->HalFunc.SetHwRegHandler( Adapter, HW_VAR_LBK_MODE, &tmpU1b);
	write_nic_byte(dev, LBKMD_SEL, tmpU1b);

	// Set RCR
	write_nic_dword(dev, RCR, priv->ReceiveConfig);
	RT_TRACE(COMP_INIT, "MacConfigAfterFwDownload(): Current RCR settings(%#x)\n", priv->ReceiveConfig);


	// Set RQPN
	//
	// <Roger_Notes> 2008.08.18.
	// 6 endpoints:
	// (1) Page number on CMDQ is 0x03.
	// (2) Page number on BCNQ, HQ and MGTQ is 0.
	// (3) Page number on BKQ, BEQ, VIQ and VOQ are 0x07.
	// (4) Page number on PUBQ is 0xdd
	//
	// 11 endpoints:
	// (1) Page number on CMDQ is 0x00.
	// (2) Page number on BCNQ is 0x02, HQ and MGTQ are 0x03.
	// (3) Page number on BKQ, BEQ, VIQ and VOQ are 0x07.
	// (4) Page number on PUBQ is 0xd8
	//
	//write_nic_dword(Adapter, 0xa0, 0x07070707); //BKQ, BEQ, VIQ and VOQ
	//write_nic_byte(dev, 0xa4, 0x00); // HCCAQ

	// Fix the RX FIFO issue(USB error), Rivesed by Roger, 2008-06-14
	tmpU1b = read_nic_byte_E(dev, 0x5C);
	write_nic_byte_E(dev, 0x5C, tmpU1b|BIT7);

	// For EFUSE init configuration.
	//if (IS_BOOT_FROM_EFUSE(Adapter))	// We may R/W EFUSE in EFUSE mode
	if (priv->bBootFromEfuse)
	{
		u8	tempval;

		tempval = read_nic_byte(dev, SYS_ISO_CTRL+1);
		tempval &= 0xFE;
		write_nic_byte(dev, SYS_ISO_CTRL+1, tempval);

		// Enable LDO 2.5V for write action
		//tempval = read_nic_byte(Adapter, EFUSE_TEST+3);
		//write_nic_byte(Adapter, EFUSE_TEST+3, (tempval | 0x80));

		// Change Efuse Clock for write action
		//write_nic_byte(Adapter, EFUSE_CLK, 0x03);

		// Change Program timing
		write_nic_byte(dev, EFUSE_CTRL+3, 0x72);
		//printk("!!!!!!!!!!!!!!!!!!!!!%s: write 0x33 with 0x72\n",__FUNCTION__);
		RT_TRACE(COMP_INIT, "EFUSE CONFIG OK\n");
	}


	RT_TRACE(COMP_INIT, "<---MacConfigAfterFwDownload()\n");
}