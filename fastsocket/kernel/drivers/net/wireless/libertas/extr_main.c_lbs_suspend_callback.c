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
struct lbs_private {scalar_t__ fw_ready; scalar_t__ mesh_dev; scalar_t__ dev; } ;
struct cmd_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LBS_DEB_FW ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_device_detach (scalar_t__) ; 

__attribute__((used)) static int lbs_suspend_callback(struct lbs_private *priv, unsigned long dummy,
				struct cmd_header *cmd)
{
	lbs_deb_enter(LBS_DEB_FW);

	netif_device_detach(priv->dev);
	if (priv->mesh_dev)
		netif_device_detach(priv->mesh_dev);

	priv->fw_ready = 0;
	lbs_deb_leave(LBS_DEB_FW);
	return 0;
}