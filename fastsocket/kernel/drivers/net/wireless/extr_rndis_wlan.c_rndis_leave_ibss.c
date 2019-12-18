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
struct wiphy {int dummy; } ;
struct usbnet {int /*<<< orphan*/  net; } ;
struct rndis_wlan_private {int connected; int /*<<< orphan*/  bssid; struct usbnet* usbdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int deauthenticate (struct usbnet*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct rndis_wlan_private* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int rndis_leave_ibss(struct wiphy *wiphy, struct net_device *dev)
{
	struct rndis_wlan_private *priv = wiphy_priv(wiphy);
	struct usbnet *usbdev = priv->usbdev;

	netdev_dbg(usbdev->net, "cfg80211.leave_ibss()\n");

	priv->connected = false;
	memset(priv->bssid, 0, ETH_ALEN);

	return deauthenticate(usbdev);
}