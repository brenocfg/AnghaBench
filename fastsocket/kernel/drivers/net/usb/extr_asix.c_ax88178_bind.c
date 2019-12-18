#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_5__ {int phy_id_mask; int reg_num_mask; int supports_gmii; int /*<<< orphan*/  phy_id; int /*<<< orphan*/  (* mdio_write ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  mdio_read; TYPE_3__* dev; } ;
struct usbnet {int rx_urb_size; int /*<<< orphan*/  driver_priv; TYPE_1__* driver_info; TYPE_2__ mii; TYPE_3__* net; int /*<<< orphan*/  data; } ;
struct usb_interface {int dummy; } ;
struct asix_data {int phymode; int ledmode; } ;
struct asix_common_private {int dummy; } ;
typedef  scalar_t__ __le16 ;
struct TYPE_6__ {int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int ADVERTISE_1000FULL ; 
 int ADVERTISE_ALL ; 
 int ADVERTISE_CSMA ; 
 int ADVERTISE_PAUSE_CAP ; 
 int /*<<< orphan*/  AX88178_MEDIUM_DEFAULT ; 
 int /*<<< orphan*/  AX_CMD_READ_EEPROM ; 
 int /*<<< orphan*/  AX_CMD_READ_GPIOS ; 
 int /*<<< orphan*/  AX_CMD_READ_NODE_ID ; 
 int /*<<< orphan*/  AX_CMD_WRITE_DISABLE ; 
 int /*<<< orphan*/  AX_CMD_WRITE_ENABLE ; 
 int /*<<< orphan*/  AX_DEFAULT_RX_CTL ; 
 int AX_GPIO_GPO1EN ; 
 int AX_GPIO_GPO_1 ; 
 int AX_GPIO_RSE ; 
 int AX_SWRESET_IPPD ; 
 int AX_SWRESET_PRL ; 
 int BMCR_ANENABLE ; 
 int BMCR_RESET ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 int FLAG_FRAMING_AX ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 int PHY_MODE_MARVELL ; 
 int /*<<< orphan*/  asix_get_phy_addr (struct usbnet*) ; 
 int asix_get_phyid (struct usbnet*) ; 
 int /*<<< orphan*/  asix_mdio_read ; 
 int /*<<< orphan*/  asix_mdio_write (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int asix_read_cmd (struct usbnet*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  asix_sw_reset (struct usbnet*,int) ; 
 int /*<<< orphan*/  asix_write_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asix_write_gpio (struct usbnet*,int,int) ; 
 int asix_write_medium_mode (struct usbnet*,int /*<<< orphan*/ ) ; 
 int asix_write_rx_ctl (struct usbnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ax88178_ethtool_ops ; 
 int /*<<< orphan*/  ax88178_netdev_ops ; 
 scalar_t__ cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dbg (char*,...) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  marvell_phy_init (struct usbnet*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  mii_nway_restart (TYPE_2__*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usbnet_get_endpoints (struct usbnet*,struct usb_interface*) ; 

__attribute__((used)) static int ax88178_bind(struct usbnet *dev, struct usb_interface *intf)
{
	struct asix_data *data = (struct asix_data *)&dev->data;
	int ret;
	u8 buf[ETH_ALEN];
	__le16 eeprom;
	u8 status;
	int gpio0 = 0;
	u32 phyid;

	usbnet_get_endpoints(dev,intf);

	asix_read_cmd(dev, AX_CMD_READ_GPIOS, 0, 0, 1, &status);
	dbg("GPIO Status: 0x%04x", status);

	asix_write_cmd(dev, AX_CMD_WRITE_ENABLE, 0, 0, 0, NULL);
	asix_read_cmd(dev, AX_CMD_READ_EEPROM, 0x0017, 0, 2, &eeprom);
	asix_write_cmd(dev, AX_CMD_WRITE_DISABLE, 0, 0, 0, NULL);

	dbg("EEPROM index 0x17 is 0x%04x", eeprom);

	if (eeprom == cpu_to_le16(0xffff)) {
		data->phymode = PHY_MODE_MARVELL;
		data->ledmode = 0;
		gpio0 = 1;
	} else {
		data->phymode = le16_to_cpu(eeprom) & 7;
		data->ledmode = le16_to_cpu(eeprom) >> 8;
		gpio0 = (le16_to_cpu(eeprom) & 0x80) ? 0 : 1;
	}
	dbg("GPIO0: %d, PhyMode: %d", gpio0, data->phymode);

	asix_write_gpio(dev, AX_GPIO_RSE | AX_GPIO_GPO_1 | AX_GPIO_GPO1EN, 40);
	if ((le16_to_cpu(eeprom) >> 8) != 1) {
		asix_write_gpio(dev, 0x003c, 30);
		asix_write_gpio(dev, 0x001c, 300);
		asix_write_gpio(dev, 0x003c, 30);
	} else {
		dbg("gpio phymode == 1 path");
		asix_write_gpio(dev, AX_GPIO_GPO1EN, 30);
		asix_write_gpio(dev, AX_GPIO_GPO1EN | AX_GPIO_GPO_1, 30);
	}

	asix_sw_reset(dev, 0);
	msleep(150);

	asix_sw_reset(dev, AX_SWRESET_PRL | AX_SWRESET_IPPD);
	msleep(150);

	asix_write_rx_ctl(dev, 0);

	/* Get the MAC address */
	if ((ret = asix_read_cmd(dev, AX_CMD_READ_NODE_ID,
				0, 0, ETH_ALEN, buf)) < 0) {
		dbg("Failed to read MAC address: %d", ret);
		goto out;
	}
	memcpy(dev->net->dev_addr, buf, ETH_ALEN);

	/* Initialize MII structure */
	dev->mii.dev = dev->net;
	dev->mii.mdio_read = asix_mdio_read;
	dev->mii.mdio_write = asix_mdio_write;
	dev->mii.phy_id_mask = 0x1f;
	dev->mii.reg_num_mask = 0xff;
	dev->mii.supports_gmii = 1;
	dev->mii.phy_id = asix_get_phy_addr(dev);

	dev->net->netdev_ops = &ax88178_netdev_ops;
	dev->net->ethtool_ops = &ax88178_ethtool_ops;

	phyid = asix_get_phyid(dev);
	dbg("PHYID=0x%08x", phyid);

	if (data->phymode == PHY_MODE_MARVELL) {
		marvell_phy_init(dev);
		msleep(60);
	}

	asix_mdio_write(dev->net, dev->mii.phy_id, MII_BMCR,
			BMCR_RESET | BMCR_ANENABLE);
	asix_mdio_write(dev->net, dev->mii.phy_id, MII_ADVERTISE,
			ADVERTISE_ALL | ADVERTISE_CSMA | ADVERTISE_PAUSE_CAP);
	asix_mdio_write(dev->net, dev->mii.phy_id, MII_CTRL1000,
			ADVERTISE_1000FULL);

	mii_nway_restart(&dev->mii);

	if ((ret = asix_write_medium_mode(dev, AX88178_MEDIUM_DEFAULT)) < 0)
		goto out;

	if ((ret = asix_write_rx_ctl(dev, AX_DEFAULT_RX_CTL)) < 0)
		goto out;

	/* Asix framing packs multiple eth frames into a 2K usb bulk transfer */
	if (dev->driver_info->flags & FLAG_FRAMING_AX) {
		/* hard_mtu  is still the default - the device does not support
		   jumbo eth frames */
		dev->rx_urb_size = 2048;
	}

	dev->driver_priv = kzalloc(sizeof(struct asix_common_private), GFP_KERNEL);
	if (!dev->driver_priv)
		return -ENOMEM;
	return 0;

out:
	return ret;
}