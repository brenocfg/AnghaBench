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
struct TYPE_4__ {int /*<<< orphan*/  sa_family; int /*<<< orphan*/  sa_data; } ;
union iwreq_data {TYPE_2__ ap_addr; } ;
struct hermes {TYPE_1__* ops; } ;
struct orinoco_private {struct hermes hw; struct net_device* ndev; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int (* read_ltv ) (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  HERMES_RID_CURRENTBSSID ; 
 int /*<<< orphan*/  SIOCGIWAP ; 
 int /*<<< orphan*/  USER_BAP ; 
 int stub1 (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wireless_send_event (struct net_device*,int /*<<< orphan*/ ,union iwreq_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void orinoco_send_bssid_wevent(struct orinoco_private *priv)
{
	struct net_device *dev = priv->ndev;
	struct hermes *hw = &priv->hw;
	union iwreq_data wrqu;
	int err;

	err = hw->ops->read_ltv(hw, USER_BAP, HERMES_RID_CURRENTBSSID,
				ETH_ALEN, NULL, wrqu.ap_addr.sa_data);
	if (err != 0)
		return;

	wrqu.ap_addr.sa_family = ARPHRD_ETHER;

	/* Send event to user space */
	wireless_send_event(dev, SIOCGIWAP, &wrqu, NULL);
}