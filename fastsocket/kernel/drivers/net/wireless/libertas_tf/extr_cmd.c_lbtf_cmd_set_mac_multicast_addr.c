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
typedef  int u16 ;
struct lbtf_private {int nr_of_multicastmacaddr; int /*<<< orphan*/  multicastlist; } ;
struct TYPE_2__ {void* size; } ;
struct cmd_ds_mac_multicast_addr {TYPE_1__ hdr; int /*<<< orphan*/  maclist; void* nr_of_adrs; void* action; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int CMD_ACT_SET ; 
 int /*<<< orphan*/  CMD_MAC_MULTICAST_ADR ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  LBTF_DEB_CMD ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  lbtf_cmd_async (struct lbtf_private*,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  lbtf_deb_cmd (char*,void*) ; 
 int /*<<< orphan*/  lbtf_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int lbtf_cmd_set_mac_multicast_addr(struct lbtf_private *priv)
{
	struct cmd_ds_mac_multicast_addr cmd;

	lbtf_deb_enter(LBTF_DEB_CMD);

	cmd.hdr.size = cpu_to_le16(sizeof(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_SET);

	cmd.nr_of_adrs = cpu_to_le16((u16) priv->nr_of_multicastmacaddr);

	lbtf_deb_cmd("MULTICAST_ADR: setting %d addresses\n", cmd.nr_of_adrs);

	memcpy(cmd.maclist, priv->multicastlist,
	       priv->nr_of_multicastmacaddr * ETH_ALEN);

	lbtf_cmd_async(priv, CMD_MAC_MULTICAST_ADR, &cmd.hdr, sizeof(cmd));

	lbtf_deb_leave(LBTF_DEB_CMD);
	return 0;
}