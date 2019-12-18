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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device_id {scalar_t__ driver_info; } ;
struct usb_device {int dummy; } ;
struct mib_fw_version {int major; int minor; } ;
struct TYPE_2__ {scalar_t__ major; int minor; } ;
struct fwentry {TYPE_1__ fw_version; } ;
struct at76_priv {int board_type; int /*<<< orphan*/  fw_version; } ;
typedef  int /*<<< orphan*/  fwv ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_DEVSTART ; 
 int EBUSY ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  MIB_FW_VERSION ; 
 int OPMODE_HW_CONFIG_MODE ; 
 int OPMODE_NORMAL_NIC_WITHOUT_FLASH ; 
 int OPMODE_NORMAL_NIC_WITH_FLASH ; 
 struct at76_priv* at76_alloc_new_device (struct usb_device*) ; 
 int /*<<< orphan*/  at76_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  at76_delete_device (struct at76_priv*) ; 
 int at76_get_mib (struct usb_device*,int /*<<< orphan*/ ,struct mib_fw_version*,int) ; 
 int at76_get_op_mode (struct usb_device*) ; 
 int at76_init_new_device (struct at76_priv*,struct usb_interface*) ; 
 int at76_load_external_fw (struct usb_device*,struct fwentry*) ; 
 struct fwentry* at76_load_firmware (struct usb_device*,int) ; 
 int at76_load_internal_fw (struct usb_device*,struct fwentry*) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mib_fw_version*,int) ; 
 struct usb_device* usb_get_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct at76_priv*) ; 

__attribute__((used)) static int at76_probe(struct usb_interface *interface,
		      const struct usb_device_id *id)
{
	int ret;
	struct at76_priv *priv;
	struct fwentry *fwe;
	struct usb_device *udev;
	int op_mode;
	int need_ext_fw = 0;
	struct mib_fw_version fwv;
	int board_type = (int)id->driver_info;

	udev = usb_get_dev(interface_to_usbdev(interface));

	/* Load firmware into kernel memory */
	fwe = at76_load_firmware(udev, board_type);
	if (!fwe) {
		ret = -ENOENT;
		goto error;
	}

	op_mode = at76_get_op_mode(udev);

	at76_dbg(DBG_DEVSTART, "opmode %d", op_mode);

	/* we get OPMODE_NONE with 2.4.23, SMC2662W-AR ???
	   we get 204 with 2.4.23, Fiberline FL-WL240u (505A+RFMD2958) ??? */

	if (op_mode == OPMODE_HW_CONFIG_MODE) {
		dev_printk(KERN_ERR, &interface->dev,
			   "cannot handle a device in HW_CONFIG_MODE\n");
		ret = -EBUSY;
		goto error;
	}

	if (op_mode != OPMODE_NORMAL_NIC_WITH_FLASH
	    && op_mode != OPMODE_NORMAL_NIC_WITHOUT_FLASH) {
		/* download internal firmware part */
		dev_printk(KERN_DEBUG, &interface->dev,
			   "downloading internal firmware\n");
		ret = at76_load_internal_fw(udev, fwe);
		if (ret < 0) {
			dev_printk(KERN_ERR, &interface->dev,
				   "error %d downloading internal firmware\n",
				   ret);
			goto error;
		}
		usb_put_dev(udev);
		return ret;
	}

	/* Internal firmware already inside the device.  Get firmware
	 * version to test if external firmware is loaded.
	 * This works only for newer firmware, e.g. the Intersil 0.90.x
	 * says "control timeout on ep0in" and subsequent
	 * at76_get_op_mode() fail too :-( */

	/* if version >= 0.100.x.y or device with built-in flash we can
	 * query the device for the fw version */
	if ((fwe->fw_version.major > 0 || fwe->fw_version.minor >= 100)
	    || (op_mode == OPMODE_NORMAL_NIC_WITH_FLASH)) {
		ret = at76_get_mib(udev, MIB_FW_VERSION, &fwv, sizeof(fwv));
		if (ret < 0 || (fwv.major | fwv.minor) == 0)
			need_ext_fw = 1;
	} else
		/* No way to check firmware version, reload to be sure */
		need_ext_fw = 1;

	if (need_ext_fw) {
		dev_printk(KERN_DEBUG, &interface->dev,
			   "downloading external firmware\n");

		ret = at76_load_external_fw(udev, fwe);
		if (ret)
			goto error;

		/* Re-check firmware version */
		ret = at76_get_mib(udev, MIB_FW_VERSION, &fwv, sizeof(fwv));
		if (ret < 0) {
			dev_printk(KERN_ERR, &interface->dev,
				   "error %d getting firmware version\n", ret);
			goto error;
		}
	}

	priv = at76_alloc_new_device(udev);
	if (!priv) {
		ret = -ENOMEM;
		goto error;
	}

	usb_set_intfdata(interface, priv);

	memcpy(&priv->fw_version, &fwv, sizeof(struct mib_fw_version));
	priv->board_type = board_type;

	ret = at76_init_new_device(priv, interface);
	if (ret < 0)
		at76_delete_device(priv);

	return ret;

error:
	usb_put_dev(udev);
	return ret;
}