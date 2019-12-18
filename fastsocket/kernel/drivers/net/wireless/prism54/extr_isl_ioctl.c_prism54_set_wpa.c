#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct net_device {int /*<<< orphan*/  name; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_5__ {int wpa; int /*<<< orphan*/  mib_sem; } ;
typedef  TYPE_1__ islpci_private ;
typedef  int __u32 ;

/* Variables and functions */
 int DOT11_AUTH_OS ; 
 int DOT11_MLME_AUTO ; 
 int DOT11_MLME_EXTENDED ; 
 int /*<<< orphan*/  DOT11_OID_AUTHENABLE ; 
 int /*<<< orphan*/  DOT11_OID_DOT1XENABLE ; 
 int /*<<< orphan*/  DOT11_OID_EXUNENCRYPTED ; 
 int /*<<< orphan*/  DOT11_OID_MLMEAUTOLEVEL ; 
 int /*<<< orphan*/  DOT11_OID_PRIVACYINVOKED ; 
 scalar_t__ PRV_STATE_INIT ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ islpci_get_state (TYPE_1__*) ; 
 int /*<<< orphan*/  mgt_set_request (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
prism54_set_wpa(struct net_device *ndev, struct iw_request_info *info,
		__u32 * uwrq, char *extra)
{
	islpci_private *priv = netdev_priv(ndev);
	u32 mlme, authen, dot1x, filter, wep;

	if (islpci_get_state(priv) < PRV_STATE_INIT)
		return 0;

	wep = 1; /* For privacy invoked */
	filter = 1; /* Filter out all unencrypted frames */
	dot1x = 0x01; /* To enable eap filter */
	mlme = DOT11_MLME_EXTENDED;
	authen = DOT11_AUTH_OS; /* Only WEP uses _SK and _BOTH */

	down_write(&priv->mib_sem);
	priv->wpa = *uwrq;

	switch (priv->wpa) {
		default:
		case 0: /* Clears/disables WPA and friends */
			wep = 0;
			filter = 0; /* Do not filter un-encrypted data */
			dot1x = 0;
			mlme = DOT11_MLME_AUTO;
			printk("%s: Disabling WPA\n", ndev->name);
			break;
		case 2:
		case 1: /* WPA */
			printk("%s: Enabling WPA\n", ndev->name);
			break;
	}
	up_write(&priv->mib_sem);

	mgt_set_request(priv, DOT11_OID_AUTHENABLE, 0, &authen);
	mgt_set_request(priv, DOT11_OID_PRIVACYINVOKED, 0, &wep);
	mgt_set_request(priv, DOT11_OID_EXUNENCRYPTED, 0, &filter);
	mgt_set_request(priv, DOT11_OID_DOT1XENABLE, 0, &dot1x);
	mgt_set_request(priv, DOT11_OID_MLMEAUTOLEVEL, 0, &mlme);

	return 0;
}