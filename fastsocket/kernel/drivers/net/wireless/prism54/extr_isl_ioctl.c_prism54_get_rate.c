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
union oid_res_t {int u; char* ptr; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int value; int fixed; } ;
typedef  int /*<<< orphan*/  islpci_private ;

/* Variables and functions */
 int /*<<< orphan*/  DOT11_OID_RATES ; 
 int /*<<< orphan*/  GEN_OID_LINKSTATE ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int mgt_get_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,union oid_res_t*) ; 
 int /*<<< orphan*/ * netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
prism54_get_rate(struct net_device *ndev,
		 struct iw_request_info *info,
		 struct iw_param *vwrq, char *extra)
{
	islpci_private *priv = netdev_priv(ndev);
	int rvalue;
	char *data;
	union oid_res_t r;

	/* Get the current bit rate */
	if ((rvalue = mgt_get_request(priv, GEN_OID_LINKSTATE, 0, NULL, &r)))
		return rvalue;
	vwrq->value = r.u * 500000;

	/* request the device for the enabled rates */
	rvalue = mgt_get_request(priv, DOT11_OID_RATES, 0, NULL, &r);
	if (rvalue) {
		kfree(r.ptr);
		return rvalue;
	}
	data = r.ptr;
	vwrq->fixed = (data[0] != 0) && (data[1] == 0);
	kfree(r.ptr);

	return 0;
}