#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct if_usb_card {scalar_t__ bootcmdresp; int CRC_OK; int fwseqnum; TYPE_2__* fw; scalar_t__ fwdnldover; int /*<<< orphan*/  rx_urb; int /*<<< orphan*/  fw_timeout; scalar_t__ surprise_removed; int /*<<< orphan*/  fw_wq; scalar_t__ fwfinalblk; scalar_t__ totalbytes; scalar_t__ fwlastblksent; int /*<<< orphan*/  tx_urb; TYPE_1__* udev; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BOOT_CMD_RESP_NOT_SUPPORTED ; 
 int EINVAL ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  LBS_DEB_USB ; 
 scalar_t__ check_fwfile_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_usb_issue_boot_command (struct if_usb_card*,int) ; 
 int /*<<< orphan*/  if_usb_reset_device (struct if_usb_card*) ; 
 int /*<<< orphan*/  if_usb_send_fw_pkt (struct if_usb_card*) ; 
 scalar_t__ if_usb_submit_rx_urb (struct if_usb_card*) ; 
 scalar_t__ if_usb_submit_rx_urb_fwload (struct if_usb_card*) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbs_deb_usbd (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lbs_pr_err (char*,...) ; 
 int /*<<< orphan*/  lbs_pr_info (char*,...) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  release_firmware (TYPE_2__*) ; 
 int request_firmware (TYPE_2__**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __if_usb_prog_firmware(struct if_usb_card *cardp,
					const char *fwname, int cmd)
{
	int i = 0;
	static int reset_count = 10;
	int ret = 0;

	lbs_deb_enter(LBS_DEB_USB);

	ret = request_firmware(&cardp->fw, fwname, &cardp->udev->dev);
	if (ret < 0) {
		lbs_pr_err("request_firmware() failed with %#x\n", ret);
		lbs_pr_err("firmware %s not found\n", fwname);
		goto done;
	}

	if (check_fwfile_format(cardp->fw->data, cardp->fw->size)) {
		ret = -EINVAL;
		goto release_fw;
	}

	/* Cancel any pending usb business */
	usb_kill_urb(cardp->rx_urb);
	usb_kill_urb(cardp->tx_urb);

	cardp->fwlastblksent = 0;
	cardp->fwdnldover = 0;
	cardp->totalbytes = 0;
	cardp->fwfinalblk = 0;
	cardp->bootcmdresp = 0;

restart:
	if (if_usb_submit_rx_urb_fwload(cardp) < 0) {
		lbs_deb_usbd(&cardp->udev->dev, "URB submission is failed\n");
		ret = -EIO;
		goto release_fw;
	}

	cardp->bootcmdresp = 0;
	do {
		int j = 0;
		i++;
		if_usb_issue_boot_command(cardp, cmd);
		/* wait for command response */
		do {
			j++;
			msleep_interruptible(100);
		} while (cardp->bootcmdresp == 0 && j < 10);
	} while (cardp->bootcmdresp == 0 && i < 5);

	if (cardp->bootcmdresp == BOOT_CMD_RESP_NOT_SUPPORTED) {
		/* Return to normal operation */
		ret = -EOPNOTSUPP;
		usb_kill_urb(cardp->rx_urb);
		usb_kill_urb(cardp->tx_urb);
		if (if_usb_submit_rx_urb(cardp) < 0)
			ret = -EIO;
		goto release_fw;
	} else if (cardp->bootcmdresp <= 0) {
		if (--reset_count >= 0) {
			if_usb_reset_device(cardp);
			goto restart;
		}
		ret = -EIO;
		goto release_fw;
	}

	i = 0;

	cardp->totalbytes = 0;
	cardp->fwlastblksent = 0;
	cardp->CRC_OK = 1;
	cardp->fwdnldover = 0;
	cardp->fwseqnum = -1;
	cardp->totalbytes = 0;
	cardp->fwfinalblk = 0;

	/* Send the first firmware packet... */
	if_usb_send_fw_pkt(cardp);

	/* ... and wait for the process to complete */
	wait_event_interruptible(cardp->fw_wq, cardp->surprise_removed || cardp->fwdnldover);

	del_timer_sync(&cardp->fw_timeout);
	usb_kill_urb(cardp->rx_urb);

	if (!cardp->fwdnldover) {
		lbs_pr_info("failed to load fw, resetting device!\n");
		if (--reset_count >= 0) {
			if_usb_reset_device(cardp);
			goto restart;
		}

		lbs_pr_info("FW download failure, time = %d ms\n", i * 100);
		ret = -EIO;
		goto release_fw;
	}

 release_fw:
	release_firmware(cardp->fw);
	cardp->fw = NULL;

 done:
	lbs_deb_leave_args(LBS_DEB_USB, "ret %d", ret);
	return ret;
}