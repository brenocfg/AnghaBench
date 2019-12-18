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
typedef  int /*<<< orphan*/  ulong ;
typedef  int u32 ;
struct usbnet {int rx_urb_size; struct net_device* net; TYPE_1__* udev; scalar_t__* data; } ;
struct smsc95xx_priv {int mac_cr; int /*<<< orphan*/  use_tx_csum; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_2__ {scalar_t__ speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFC_CFG ; 
 int AFC_CFG_DEFAULT ; 
 int /*<<< orphan*/  BULK_IN_DLY ; 
 int /*<<< orphan*/  BURST_CAP ; 
 int DEFAULT_BULK_IN_DELAY ; 
 int DEFAULT_FS_BURST_CAP_SIZE ; 
 int DEFAULT_HS_BURST_CAP_SIZE ; 
 int EIO ; 
 scalar_t__ ETH_P_8021Q ; 
 int /*<<< orphan*/  FLOW ; 
 int FS_USB_PKT_SIZE ; 
 int HS_USB_PKT_SIZE ; 
 int /*<<< orphan*/  HW_CFG ; 
 int HW_CFG_BCE_ ; 
 int HW_CFG_BIR_ ; 
 int HW_CFG_LRST_ ; 
 int HW_CFG_MEF_ ; 
 int HW_CFG_RXDOFF_ ; 
 int /*<<< orphan*/  ID_REV ; 
 int /*<<< orphan*/  INT_EP_CTL ; 
 int INT_EP_CTL_PHY_INT_ ; 
 int /*<<< orphan*/  INT_STS ; 
 int /*<<< orphan*/  LED_GPIO_CFG ; 
 int LED_GPIO_CFG_FDX_LED ; 
 int LED_GPIO_CFG_LNK_LED ; 
 int LED_GPIO_CFG_SPD_LED ; 
 int /*<<< orphan*/  MAC_CR ; 
 int MAX_SINGLE_PACKET_SIZE ; 
 int NET_IP_ALIGN ; 
 int PM_CTL_PHY_RST_ ; 
 int /*<<< orphan*/  PM_CTRL ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  VLAN1 ; 
 int /*<<< orphan*/  devdbg (struct usbnet*,char*,...) ; 
 int /*<<< orphan*/  devwarn (struct usbnet*,char*,...) ; 
 int /*<<< orphan*/  ethtool_op_set_tx_hw_csum (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ netif_msg_ifup (struct usbnet*) ; 
 int /*<<< orphan*/  smsc95xx_init_mac_address (struct usbnet*) ; 
 scalar_t__ smsc95xx_phy_initialize (struct usbnet*) ; 
 int smsc95xx_read_reg (struct usbnet*,int /*<<< orphan*/ ,int*) ; 
 int smsc95xx_set_csums (struct usbnet*) ; 
 int smsc95xx_set_mac_address (struct usbnet*) ; 
 int /*<<< orphan*/  smsc95xx_set_multicast (struct net_device*) ; 
 int /*<<< orphan*/  smsc95xx_start_rx_path (struct usbnet*) ; 
 int /*<<< orphan*/  smsc95xx_start_tx_path (struct usbnet*) ; 
 int smsc95xx_write_reg (struct usbnet*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ turbo_mode ; 

__attribute__((used)) static int smsc95xx_reset(struct usbnet *dev)
{
	struct smsc95xx_priv *pdata = (struct smsc95xx_priv *)(dev->data[0]);
	struct net_device *netdev = dev->net;
	u32 read_buf, write_buf, burst_cap;
	int ret = 0, timeout;

	if (netif_msg_ifup(dev))
		devdbg(dev, "entering smsc95xx_reset");

	write_buf = HW_CFG_LRST_;
	ret = smsc95xx_write_reg(dev, HW_CFG, write_buf);
	if (ret < 0) {
		devwarn(dev, "Failed to write HW_CFG_LRST_ bit in HW_CFG "
			"register, ret = %d", ret);
		return ret;
	}

	timeout = 0;
	do {
		ret = smsc95xx_read_reg(dev, HW_CFG, &read_buf);
		if (ret < 0) {
			devwarn(dev, "Failed to read HW_CFG: %d", ret);
			return ret;
		}
		msleep(10);
		timeout++;
	} while ((read_buf & HW_CFG_LRST_) && (timeout < 100));

	if (timeout >= 100) {
		devwarn(dev, "timeout waiting for completion of Lite Reset");
		return ret;
	}

	write_buf = PM_CTL_PHY_RST_;
	ret = smsc95xx_write_reg(dev, PM_CTRL, write_buf);
	if (ret < 0) {
		devwarn(dev, "Failed to write PM_CTRL: %d", ret);
		return ret;
	}

	timeout = 0;
	do {
		ret = smsc95xx_read_reg(dev, PM_CTRL, &read_buf);
		if (ret < 0) {
			devwarn(dev, "Failed to read PM_CTRL: %d", ret);
			return ret;
		}
		msleep(10);
		timeout++;
	} while ((read_buf & PM_CTL_PHY_RST_) && (timeout < 100));

	if (timeout >= 100) {
		devwarn(dev, "timeout waiting for PHY Reset");
		return ret;
	}

	smsc95xx_init_mac_address(dev);

	ret = smsc95xx_set_mac_address(dev);
	if (ret < 0)
		return ret;

	if (netif_msg_ifup(dev))
		devdbg(dev, "MAC Address: %pM", dev->net->dev_addr);

	ret = smsc95xx_read_reg(dev, HW_CFG, &read_buf);
	if (ret < 0) {
		devwarn(dev, "Failed to read HW_CFG: %d", ret);
		return ret;
	}

	if (netif_msg_ifup(dev))
		devdbg(dev, "Read Value from HW_CFG : 0x%08x", read_buf);

	read_buf |= HW_CFG_BIR_;

	ret = smsc95xx_write_reg(dev, HW_CFG, read_buf);
	if (ret < 0) {
		devwarn(dev, "Failed to write HW_CFG_BIR_ bit in HW_CFG "
			"register, ret = %d", ret);
		return ret;
	}

	ret = smsc95xx_read_reg(dev, HW_CFG, &read_buf);
	if (ret < 0) {
		devwarn(dev, "Failed to read HW_CFG: %d", ret);
		return ret;
	}
	if (netif_msg_ifup(dev))
		devdbg(dev, "Read Value from HW_CFG after writing "
			"HW_CFG_BIR_: 0x%08x", read_buf);

	if (!turbo_mode) {
		burst_cap = 0;
		dev->rx_urb_size = MAX_SINGLE_PACKET_SIZE;
	} else if (dev->udev->speed == USB_SPEED_HIGH) {
		burst_cap = DEFAULT_HS_BURST_CAP_SIZE / HS_USB_PKT_SIZE;
		dev->rx_urb_size = DEFAULT_HS_BURST_CAP_SIZE;
	} else {
		burst_cap = DEFAULT_FS_BURST_CAP_SIZE / FS_USB_PKT_SIZE;
		dev->rx_urb_size = DEFAULT_FS_BURST_CAP_SIZE;
	}

	if (netif_msg_ifup(dev))
		devdbg(dev, "rx_urb_size=%ld", (ulong)dev->rx_urb_size);

	ret = smsc95xx_write_reg(dev, BURST_CAP, burst_cap);
	if (ret < 0) {
		devwarn(dev, "Failed to write BURST_CAP: %d", ret);
		return ret;
	}

	ret = smsc95xx_read_reg(dev, BURST_CAP, &read_buf);
	if (ret < 0) {
		devwarn(dev, "Failed to read BURST_CAP: %d", ret);
		return ret;
	}
	if (netif_msg_ifup(dev))
		devdbg(dev, "Read Value from BURST_CAP after writing: 0x%08x",
			read_buf);

	read_buf = DEFAULT_BULK_IN_DELAY;
	ret = smsc95xx_write_reg(dev, BULK_IN_DLY, read_buf);
	if (ret < 0) {
		devwarn(dev, "ret = %d", ret);
		return ret;
	}

	ret = smsc95xx_read_reg(dev, BULK_IN_DLY, &read_buf);
	if (ret < 0) {
		devwarn(dev, "Failed to read BULK_IN_DLY: %d", ret);
		return ret;
	}
	if (netif_msg_ifup(dev))
		devdbg(dev, "Read Value from BULK_IN_DLY after writing: "
			"0x%08x", read_buf);

	ret = smsc95xx_read_reg(dev, HW_CFG, &read_buf);
	if (ret < 0) {
		devwarn(dev, "Failed to read HW_CFG: %d", ret);
		return ret;
	}
	if (netif_msg_ifup(dev))
		devdbg(dev, "Read Value from HW_CFG: 0x%08x", read_buf);

	if (turbo_mode)
		read_buf |= (HW_CFG_MEF_ | HW_CFG_BCE_);

	read_buf &= ~HW_CFG_RXDOFF_;

	/* set Rx data offset=2, Make IP header aligns on word boundary. */
	read_buf |= NET_IP_ALIGN << 9;

	ret = smsc95xx_write_reg(dev, HW_CFG, read_buf);
	if (ret < 0) {
		devwarn(dev, "Failed to write HW_CFG register, ret=%d", ret);
		return ret;
	}

	ret = smsc95xx_read_reg(dev, HW_CFG, &read_buf);
	if (ret < 0) {
		devwarn(dev, "Failed to read HW_CFG: %d", ret);
		return ret;
	}
	if (netif_msg_ifup(dev))
		devdbg(dev, "Read Value from HW_CFG after writing: 0x%08x",
			read_buf);

	write_buf = 0xFFFFFFFF;
	ret = smsc95xx_write_reg(dev, INT_STS, write_buf);
	if (ret < 0) {
		devwarn(dev, "Failed to write INT_STS register, ret=%d", ret);
		return ret;
	}

	ret = smsc95xx_read_reg(dev, ID_REV, &read_buf);
	if (ret < 0) {
		devwarn(dev, "Failed to read ID_REV: %d", ret);
		return ret;
	}
	if (netif_msg_ifup(dev))
		devdbg(dev, "ID_REV = 0x%08x", read_buf);

	/* Configure GPIO pins as LED outputs */
	write_buf = LED_GPIO_CFG_SPD_LED | LED_GPIO_CFG_LNK_LED |
		LED_GPIO_CFG_FDX_LED;
	ret = smsc95xx_write_reg(dev, LED_GPIO_CFG, write_buf);
	if (ret < 0) {
		devwarn(dev, "Failed to write LED_GPIO_CFG register, ret=%d",
			ret);
		return ret;
	}

	/* Init Tx */
	write_buf = 0;
	ret = smsc95xx_write_reg(dev, FLOW, write_buf);
	if (ret < 0) {
		devwarn(dev, "Failed to write FLOW: %d", ret);
		return ret;
	}

	read_buf = AFC_CFG_DEFAULT;
	ret = smsc95xx_write_reg(dev, AFC_CFG, read_buf);
	if (ret < 0) {
		devwarn(dev, "Failed to write AFC_CFG: %d", ret);
		return ret;
	}

	/* Don't need mac_cr_lock during initialisation */
	ret = smsc95xx_read_reg(dev, MAC_CR, &pdata->mac_cr);
	if (ret < 0) {
		devwarn(dev, "Failed to read MAC_CR: %d", ret);
		return ret;
	}

	/* Init Rx */
	/* Set Vlan */
	write_buf = (u32)ETH_P_8021Q;
	ret = smsc95xx_write_reg(dev, VLAN1, write_buf);
	if (ret < 0) {
		devwarn(dev, "Failed to write VAN1: %d", ret);
		return ret;
	}

	/* Enable or disable checksum offload engines */
	ethtool_op_set_tx_hw_csum(netdev, pdata->use_tx_csum);
	ret = smsc95xx_set_csums(dev);
	if (ret < 0) {
		devwarn(dev, "Failed to set csum offload: %d", ret);
		return ret;
	}

	smsc95xx_set_multicast(dev->net);

	if (smsc95xx_phy_initialize(dev) < 0)
		return -EIO;

	ret = smsc95xx_read_reg(dev, INT_EP_CTL, &read_buf);
	if (ret < 0) {
		devwarn(dev, "Failed to read INT_EP_CTL: %d", ret);
		return ret;
	}

	/* enable PHY interrupts */
	read_buf |= INT_EP_CTL_PHY_INT_;

	ret = smsc95xx_write_reg(dev, INT_EP_CTL, read_buf);
	if (ret < 0) {
		devwarn(dev, "Failed to write INT_EP_CTL: %d", ret);
		return ret;
	}

	smsc95xx_start_tx_path(dev);
	smsc95xx_start_rx_path(dev);

	if (netif_msg_ifup(dev))
		devdbg(dev, "smsc95xx_reset, return 0");
	return 0;
}