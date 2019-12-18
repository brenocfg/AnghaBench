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
struct lbs_private {unsigned long fwcapinfo; scalar_t__ dnld_sent; int /*<<< orphan*/  waitq; int /*<<< orphan*/  driver_lock; int /*<<< orphan*/ * cur_cmd; } ;
struct if_usb_card {struct lbs_private* priv; } ;

/* Variables and functions */
 int BOOT_CMD_UPDATE_BOOT2 ; 
 int BOOT_CMD_UPDATE_FW ; 
 scalar_t__ DNLD_BOOTCMD_SENT ; 
 scalar_t__ DNLD_RES_RECEIVED ; 
 int EOPNOTSUPP ; 
 int ERESTARTSYS ; 
 unsigned long FW_CAPINFO_BOOT2_UPGRADE ; 
 unsigned long FW_CAPINFO_FIRMWARE_UPGRADE ; 
 int __if_usb_prog_firmware (struct if_usb_card*,char const*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ wait_event_interruptible (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int if_usb_prog_firmware(struct if_usb_card *cardp,
				const char *fwname, int cmd)
{
	struct lbs_private *priv = cardp->priv;
	unsigned long flags, caps;
	int ret;

	caps = priv->fwcapinfo;
	if (((cmd == BOOT_CMD_UPDATE_FW) && !(caps & FW_CAPINFO_FIRMWARE_UPGRADE)) ||
	    ((cmd == BOOT_CMD_UPDATE_BOOT2) && !(caps & FW_CAPINFO_BOOT2_UPGRADE)))
		return -EOPNOTSUPP;

	/* Ensure main thread is idle. */
	spin_lock_irqsave(&priv->driver_lock, flags);
	while (priv->cur_cmd != NULL || priv->dnld_sent != DNLD_RES_RECEIVED) {
		spin_unlock_irqrestore(&priv->driver_lock, flags);
		if (wait_event_interruptible(priv->waitq,
				(priv->cur_cmd == NULL &&
				priv->dnld_sent == DNLD_RES_RECEIVED))) {
			return -ERESTARTSYS;
		}
		spin_lock_irqsave(&priv->driver_lock, flags);
	}
	priv->dnld_sent = DNLD_BOOTCMD_SENT;
	spin_unlock_irqrestore(&priv->driver_lock, flags);

	ret = __if_usb_prog_firmware(cardp, fwname, cmd);

	spin_lock_irqsave(&priv->driver_lock, flags);
	priv->dnld_sent = DNLD_RES_RECEIVED;
	spin_unlock_irqrestore(&priv->driver_lock, flags);

	wake_up_interruptible(&priv->waitq);

	return ret;
}