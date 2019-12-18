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
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  channel; } ;
struct lbs_private {scalar_t__ mesh_fw_ver; void* mesh_tlv; TYPE_1__ curbssparams; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ACT_MESH_CONFIG_START ; 
 int /*<<< orphan*/  LBS_DEB_MAIN ; 
 scalar_t__ MESH_FW_NEW ; 
 scalar_t__ MESH_FW_OLD ; 
 void* TLV_TYPE_MESH_ID ; 
 void* TLV_TYPE_OLD_MESH_ID ; 
 int /*<<< orphan*/  dev_attr_lbs_mesh ; 
 int /*<<< orphan*/  dev_attr_lbs_rtap ; 
 scalar_t__ device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lbs_add_mesh (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbs_debugfs_init_one (struct lbs_private*,struct net_device*) ; 
 int /*<<< orphan*/  lbs_init_11d (struct lbs_private*) ; 
 scalar_t__ lbs_mesh_config (struct lbs_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_pr_err (char*) ; 
 int /*<<< orphan*/  lbs_pr_info (char*,int /*<<< orphan*/ ) ; 
 int lbs_setup_firmware (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_update_channel (struct lbs_private*) ; 
 scalar_t__ register_netdev (struct net_device*) ; 

int lbs_start_card(struct lbs_private *priv)
{
	struct net_device *dev = priv->dev;
	int ret = -1;

	lbs_deb_enter(LBS_DEB_MAIN);

	/* poke the firmware */
	ret = lbs_setup_firmware(priv);
	if (ret)
		goto done;

	/* init 802.11d */
	lbs_init_11d(priv);

	if (register_netdev(dev)) {
		lbs_pr_err("cannot register ethX device\n");
		goto done;
	}

	lbs_update_channel(priv);

	/* Check mesh FW version and appropriately send the mesh start
	 * command
	 */
	if (priv->mesh_fw_ver == MESH_FW_OLD) {
		/* Enable mesh, if supported, and work out which TLV it uses.
		   0x100 + 291 is an unofficial value used in 5.110.20.pXX
		   0x100 + 37 is the official value used in 5.110.21.pXX
		   but we check them in that order because 20.pXX doesn't
		   give an error -- it just silently fails. */

		/* 5.110.20.pXX firmware will fail the command if the channel
		   doesn't match the existing channel. But only if the TLV
		   is correct. If the channel is wrong, _BOTH_ versions will
		   give an error to 0x100+291, and allow 0x100+37 to succeed.
		   It's just that 5.110.20.pXX will not have done anything
		   useful */

		priv->mesh_tlv = TLV_TYPE_OLD_MESH_ID;
		if (lbs_mesh_config(priv, CMD_ACT_MESH_CONFIG_START,
				    priv->curbssparams.channel)) {
			priv->mesh_tlv = TLV_TYPE_MESH_ID;
			if (lbs_mesh_config(priv, CMD_ACT_MESH_CONFIG_START,
					    priv->curbssparams.channel))
				priv->mesh_tlv = 0;
		}
	} else if (priv->mesh_fw_ver == MESH_FW_NEW) {
		/* 10.0.0.pXX new firmwares should succeed with TLV
		 * 0x100+37; Do not invoke command with old TLV.
		 */
		priv->mesh_tlv = TLV_TYPE_MESH_ID;
		if (lbs_mesh_config(priv, CMD_ACT_MESH_CONFIG_START,
				    priv->curbssparams.channel))
			priv->mesh_tlv = 0;
	}
	if (priv->mesh_tlv) {
		lbs_add_mesh(priv);

		if (device_create_file(&dev->dev, &dev_attr_lbs_mesh))
			lbs_pr_err("cannot register lbs_mesh attribute\n");

		/* While rtap isn't related to mesh, only mesh-enabled
		 * firmware implements the rtap functionality via
		 * CMD_802_11_MONITOR_MODE.
		 */
		if (device_create_file(&dev->dev, &dev_attr_lbs_rtap))
			lbs_pr_err("cannot register lbs_rtap attribute\n");
	}

	lbs_debugfs_init_one(priv, dev);

	lbs_pr_info("%s: Marvell WLAN 802.11 adapter\n", dev->name);

	ret = 0;

done:
	lbs_deb_leave_args(LBS_DEB_MAIN, "ret %d", ret);
	return ret;
}