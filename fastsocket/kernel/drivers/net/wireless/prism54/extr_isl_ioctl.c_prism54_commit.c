#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_4__ {scalar_t__ iw_mode; } ;
typedef  TYPE_1__ islpci_private ;

/* Variables and functions */
 int /*<<< orphan*/  DOT11_OID_SSID ; 
 scalar_t__ IW_MODE_MONITOR ; 
 int mgt_set_request (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
prism54_commit(struct net_device *ndev, struct iw_request_info *info,
	       char *cwrq, char *extra)
{
	islpci_private *priv = netdev_priv(ndev);

	/* simply re-set the last set SSID, this should commit most stuff */

	/* Commit in Monitor mode is not necessary, also setting essid
	 * in Monitor mode does not make sense and isn't allowed for this
	 * device's firmware */
	if (priv->iw_mode != IW_MODE_MONITOR)
		return mgt_set_request(priv, DOT11_OID_SSID, 0, NULL);
	return 0;
}