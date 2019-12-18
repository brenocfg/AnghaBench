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
struct sockaddr {scalar_t__ sa_family; int /*<<< orphan*/  sa_data; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
typedef  int /*<<< orphan*/  islpci_private ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int /*<<< orphan*/  DOT11_OID_BSSID ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int mgt_set_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/ * netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
prism54_set_wap(struct net_device *ndev, struct iw_request_info *info,
		struct sockaddr *awrq, char *extra)
{
	islpci_private *priv = netdev_priv(ndev);
	char bssid[6];
	int rvalue;

	if (awrq->sa_family != ARPHRD_ETHER)
		return -EINVAL;

	/* prepare the structure for the set object */
	memcpy(&bssid[0], awrq->sa_data, 6);

	/* set the bssid -- does this make sense when in AP mode? */
	rvalue = mgt_set_request(priv, DOT11_OID_BSSID, 0, &bssid);

	return (rvalue ? rvalue : -EINPROGRESS);	/* Call commit handler */
}