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
struct if_usb_card {int /*<<< orphan*/  udev; struct cmd_ds_command* ep_out_buf; } ;
struct cmd_header {int dummy; } ;
struct cmd_ds_command {void* seqnum; void* result; void* size; void* command; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int CMD_802_11_RESET ; 
 int /*<<< orphan*/  CMD_TYPE_REQUEST ; 
 int /*<<< orphan*/  LBS_DEB_USB ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_usb_reset_olpc_card (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ machine_is_olpc () ; 
 int /*<<< orphan*/  msleep (int) ; 
 int usb_reset_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_tx_block (struct if_usb_card*,struct cmd_ds_command*,int) ; 

__attribute__((used)) static int if_usb_reset_device(struct if_usb_card *cardp)
{
	struct cmd_ds_command *cmd = cardp->ep_out_buf + 4;
	int ret;

	lbs_deb_enter(LBS_DEB_USB);

	*(__le32 *)cardp->ep_out_buf = cpu_to_le32(CMD_TYPE_REQUEST);

	cmd->command = cpu_to_le16(CMD_802_11_RESET);
	cmd->size = cpu_to_le16(sizeof(struct cmd_header));
	cmd->result = cpu_to_le16(0);
	cmd->seqnum = cpu_to_le16(0x5a5a);
	usb_tx_block(cardp, cardp->ep_out_buf, 4 + sizeof(struct cmd_header));

	msleep(100);
	ret = usb_reset_device(cardp->udev);
	msleep(100);

#ifdef CONFIG_OLPC
	if (ret && machine_is_olpc())
		if_usb_reset_olpc_card(NULL);
#endif

	lbs_deb_leave_args(LBS_DEB_USB, "ret %d", ret);

	return ret;
}