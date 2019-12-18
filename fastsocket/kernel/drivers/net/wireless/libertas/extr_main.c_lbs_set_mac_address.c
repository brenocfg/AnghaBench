#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int /*<<< orphan*/  dev_addr; struct lbs_private* ml_priv; } ;
struct lbs_private {TYPE_2__* mesh_dev; int /*<<< orphan*/  current_addr; struct net_device* dev; } ;
struct TYPE_3__ {void* size; } ;
struct cmd_ds_802_11_mac_address {int /*<<< orphan*/  macadd; void* action; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_4__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_MAC_ADDRESS ; 
 int CMD_ACT_SET ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  LBS_DEB_NET ; 
 void* cpu_to_le16 (int) ; 
 int lbs_cmd_with_response (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_ds_802_11_mac_address*) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbs_deb_net (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lbs_set_mac_address(struct net_device *dev, void *addr)
{
	int ret = 0;
	struct lbs_private *priv = dev->ml_priv;
	struct sockaddr *phwaddr = addr;
	struct cmd_ds_802_11_mac_address cmd;

	lbs_deb_enter(LBS_DEB_NET);

	/* In case it was called from the mesh device */
	dev = priv->dev;

	cmd.hdr.size = cpu_to_le16(sizeof(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_SET);
	memcpy(cmd.macadd, phwaddr->sa_data, ETH_ALEN);

	ret = lbs_cmd_with_response(priv, CMD_802_11_MAC_ADDRESS, &cmd);
	if (ret) {
		lbs_deb_net("set MAC address failed\n");
		goto done;
	}

	memcpy(priv->current_addr, phwaddr->sa_data, ETH_ALEN);
	memcpy(dev->dev_addr, phwaddr->sa_data, ETH_ALEN);
	if (priv->mesh_dev)
		memcpy(priv->mesh_dev->dev_addr, phwaddr->sa_data, ETH_ALEN);

done:
	lbs_deb_leave_args(LBS_DEB_NET, "ret %d", ret);
	return ret;
}