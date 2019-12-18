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
struct if_usb_card {struct bootcmd* ep_out_buf; } ;
struct bootcmd {int cmd; int /*<<< orphan*/  pad; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOOT_CMD_MAGIC_NUMBER ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_tx_block (struct if_usb_card*,struct bootcmd*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int if_usb_issue_boot_command(struct if_usb_card *cardp, int ivalue)
{
	struct bootcmd *bootcmd = cardp->ep_out_buf;

	/* Prepare command */
	bootcmd->magic = cpu_to_le32(BOOT_CMD_MAGIC_NUMBER);
	bootcmd->cmd = ivalue;
	memset(bootcmd->pad, 0, sizeof(bootcmd->pad));

	/* Issue command */
	usb_tx_block(cardp, cardp->ep_out_buf, sizeof(*bootcmd), 0);

	return 0;
}