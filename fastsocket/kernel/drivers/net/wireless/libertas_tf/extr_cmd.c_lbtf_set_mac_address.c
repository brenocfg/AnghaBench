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
typedef  int /*<<< orphan*/  uint8_t ;
struct lbtf_private {int dummy; } ;
struct TYPE_2__ {void* size; } ;
struct cmd_ds_802_11_mac_address {TYPE_1__ hdr; int /*<<< orphan*/  macadd; void* action; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_MAC_ADDRESS ; 
 int CMD_ACT_SET ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  LBTF_DEB_CMD ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  lbtf_cmd_async (struct lbtf_private*,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  lbtf_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int lbtf_set_mac_address(struct lbtf_private *priv, uint8_t *mac_addr)
{
	struct cmd_ds_802_11_mac_address cmd;
	lbtf_deb_enter(LBTF_DEB_CMD);

	cmd.hdr.size = cpu_to_le16(sizeof(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_SET);

	memcpy(cmd.macadd, mac_addr, ETH_ALEN);

	lbtf_cmd_async(priv, CMD_802_11_MAC_ADDRESS, &cmd.hdr, sizeof(cmd));
	lbtf_deb_leave(LBTF_DEB_CMD);
	return 0;
}