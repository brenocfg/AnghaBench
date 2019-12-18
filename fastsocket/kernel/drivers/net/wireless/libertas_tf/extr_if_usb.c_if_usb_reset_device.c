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
struct if_usb_card {int /*<<< orphan*/  udev; struct cmd_ds_802_11_reset* ep_out_buf; } ;
struct TYPE_2__ {void* seqnum; void* result; void* size; void* command; } ;
struct cmd_ds_802_11_reset {void* action; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int CMD_802_11_RESET ; 
 int CMD_ACT_HALT ; 
 int /*<<< orphan*/  CMD_TYPE_REQUEST ; 
 int /*<<< orphan*/  LBTF_DEB_USB ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int usb_reset_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_tx_block (struct if_usb_card*,struct cmd_ds_802_11_reset*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int if_usb_reset_device(struct if_usb_card *cardp)
{
	struct cmd_ds_802_11_reset *cmd = cardp->ep_out_buf + 4;
	int ret;

	lbtf_deb_enter(LBTF_DEB_USB);

	*(__le32 *)cardp->ep_out_buf = cpu_to_le32(CMD_TYPE_REQUEST);

	cmd->hdr.command = cpu_to_le16(CMD_802_11_RESET);
	cmd->hdr.size = cpu_to_le16(sizeof(struct cmd_ds_802_11_reset));
	cmd->hdr.result = cpu_to_le16(0);
	cmd->hdr.seqnum = cpu_to_le16(0x5a5a);
	cmd->action = cpu_to_le16(CMD_ACT_HALT);
	usb_tx_block(cardp, cardp->ep_out_buf,
		     4 + sizeof(struct cmd_ds_802_11_reset), 0);

	msleep(100);
	ret = usb_reset_device(cardp->udev);
	msleep(100);

	lbtf_deb_leave_args(LBTF_DEB_USB, "ret %d", ret);

	return ret;
}