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
union oid_res_t {scalar_t__ u; struct obj_key* ptr; } ;
typedef  scalar_t__ u32 ;
struct obj_key {int /*<<< orphan*/  key; int /*<<< orphan*/  length; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int flags; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  islpci_private ;

/* Variables and functions */
 scalar_t__ DOT11_AUTH_BOTH ; 
 scalar_t__ DOT11_AUTH_OS ; 
 int /*<<< orphan*/  DOT11_OID_AUTHENABLE ; 
 int /*<<< orphan*/  DOT11_OID_DEFKEYID ; 
 int /*<<< orphan*/  DOT11_OID_DEFKEYX ; 
 int /*<<< orphan*/  DOT11_OID_EXUNENCRYPTED ; 
 int /*<<< orphan*/  DOT11_OID_PRIVACYINVOKED ; 
 int IW_ENCODE_DISABLED ; 
 int IW_ENCODE_INDEX ; 
 int IW_ENCODE_OPEN ; 
 int IW_ENCODE_RESTRICTED ; 
 int /*<<< orphan*/  kfree (struct obj_key*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mgt_get_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,union oid_res_t*) ; 
 int /*<<< orphan*/ * netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
prism54_get_encode(struct net_device *ndev, struct iw_request_info *info,
		   struct iw_point *dwrq, char *extra)
{
	islpci_private *priv = netdev_priv(ndev);
	struct obj_key *key;
	u32 devindex, index = (dwrq->flags & IW_ENCODE_INDEX) - 1;
	u32 authen = 0, invoke = 0, exunencrypt = 0;
	int rvalue;
	union oid_res_t r;

	/* first get the flags */
	rvalue = mgt_get_request(priv, DOT11_OID_AUTHENABLE, 0, NULL, &r);
	authen = r.u;
	rvalue |= mgt_get_request(priv, DOT11_OID_PRIVACYINVOKED, 0, NULL, &r);
	invoke = r.u;
	rvalue |= mgt_get_request(priv, DOT11_OID_EXUNENCRYPTED, 0, NULL, &r);
	exunencrypt = r.u;

	if (invoke && (authen == DOT11_AUTH_BOTH) && exunencrypt)
		dwrq->flags = IW_ENCODE_RESTRICTED;
	else if ((authen == DOT11_AUTH_OS) && !exunencrypt) {
		if (invoke)
			dwrq->flags = IW_ENCODE_OPEN;
		else
			dwrq->flags = IW_ENCODE_DISABLED;
	} else
		/* The card should not work in this state */
		dwrq->flags = 0;

	/* get the current device key index */
	rvalue |= mgt_get_request(priv, DOT11_OID_DEFKEYID, 0, NULL, &r);
	devindex = r.u;
	/* Now get the key, return it */
	if (index == -1 || index > 3)
		/* no index provided, use the current one */
		index = devindex;
	rvalue |= mgt_get_request(priv, DOT11_OID_DEFKEYX, index, NULL, &r);
	key = r.ptr;
	dwrq->length = key->length;
	memcpy(extra, key->key, dwrq->length);
	kfree(key);
	/* return the used key index */
	dwrq->flags |= devindex + 1;

	return rvalue;
}