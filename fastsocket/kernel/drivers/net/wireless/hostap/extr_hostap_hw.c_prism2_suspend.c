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
typedef  int /*<<< orphan*/  wrqu ;
struct TYPE_2__ {int /*<<< orphan*/  sa_family; } ;
union iwreq_data {TYPE_1__ ap_addr; } ;
struct net_device {int dummy; } ;
struct local_info {int /*<<< orphan*/  dev; } ;
struct hostap_interface {struct local_info* local; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  SIOCGIWAP ; 
 int /*<<< orphan*/  memset (union iwreq_data*,int /*<<< orphan*/ ,int) ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  prism2_hw_shutdown (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wireless_send_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union iwreq_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void prism2_suspend(struct net_device *dev)
{
	struct hostap_interface *iface;
	struct local_info *local;
	union iwreq_data wrqu;

	iface = netdev_priv(dev);
	local = iface->local;

	/* Send disconnect event, e.g., to trigger reassociation after resume
	 * if wpa_supplicant is used. */
	memset(&wrqu, 0, sizeof(wrqu));
	wrqu.ap_addr.sa_family = ARPHRD_ETHER;
	wireless_send_event(local->dev, SIOCGIWAP, &wrqu, NULL);

	/* Disable hardware and firmware */
	prism2_hw_shutdown(dev, 0);
}