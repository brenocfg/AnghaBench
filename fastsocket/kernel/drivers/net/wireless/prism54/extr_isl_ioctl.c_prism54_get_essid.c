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
union oid_res_t {struct obj_ssid* ptr; } ;
typedef  int /*<<< orphan*/  u8 ;
struct obj_ssid {int length; char* octets; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int flags; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  islpci_private ;

/* Variables and functions */
 int /*<<< orphan*/  DOT11_OID_SSID ; 
 scalar_t__ IW_ESSID_MAX_SIZE ; 
 int /*<<< orphan*/  kfree (struct obj_ssid*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int mgt_get_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,union oid_res_t*) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
prism54_get_essid(struct net_device *ndev, struct iw_request_info *info,
		  struct iw_point *dwrq, char *extra)
{
	islpci_private *priv = netdev_priv(ndev);
	struct obj_ssid *essid;
	union oid_res_t r;
	int rvalue;

	rvalue = mgt_get_request(priv, DOT11_OID_SSID, 0, NULL, &r);
	essid = r.ptr;

	if (essid->length) {
		dwrq->flags = 1;	/* set ESSID to ON for Wireless Extensions */
		/* if it is too big, trunk it */
		dwrq->length = min((u8)IW_ESSID_MAX_SIZE, essid->length);
	} else {
		dwrq->flags = 0;
		dwrq->length = 0;
	}
	essid->octets[essid->length] = '\0';
	memcpy(extra, essid->octets, dwrq->length);
	kfree(essid);

	return rvalue;
}