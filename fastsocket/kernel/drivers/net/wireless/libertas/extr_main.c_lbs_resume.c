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
struct lbs_private {int fw_ready; scalar_t__ mesh_dev; scalar_t__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_RSSI ; 
 int /*<<< orphan*/  LBS_DEB_FW ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_prepare_and_send_command (struct lbs_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_device_attach (scalar_t__) ; 

void lbs_resume(struct lbs_private *priv)
{
	lbs_deb_enter(LBS_DEB_FW);

	priv->fw_ready = 1;

	/* Firmware doesn't seem to give us RX packets any more
	   until we send it some command. Might as well update */
	lbs_prepare_and_send_command(priv, CMD_802_11_RSSI, 0,
				     0, 0, NULL);

	netif_device_attach(priv->dev);
	if (priv->mesh_dev)
		netif_device_attach(priv->mesh_dev);

	lbs_deb_leave(LBS_DEB_FW);
}