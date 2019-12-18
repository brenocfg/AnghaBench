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
union oid_res_t {struct obj_bsslist* ptr; int /*<<< orphan*/  u; } ;
typedef  int /*<<< orphan*/  u32 ;
struct prism2_hostapd_param {int dummy; } ;
struct obj_bsslist {int /*<<< orphan*/ * bsslist; scalar_t__ nr; } ;
struct net_device {int dummy; } ;
struct iw_request_info {scalar_t__ flags; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  islpci_private ;

/* Variables and functions */
 int /*<<< orphan*/  DOT11_OID_BSSLIST ; 
 int /*<<< orphan*/  DOT11_OID_NOISEFLOOR ; 
 int /*<<< orphan*/  IW_MAX_AP ; 
 int IW_SCAN_MAX_DATA ; 
 int /*<<< orphan*/  PRISM54_HOSTAPD ; 
 scalar_t__ PRV_STATE_INIT ; 
 scalar_t__ islpci_get_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct obj_bsslist*) ; 
 int mgt_get_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,union oid_res_t*) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * netdev_priv (struct net_device*) ; 
 char* prism54_translate_bss (struct net_device*,struct iw_request_info*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
prism2_ioctl_scan_req(struct net_device *ndev,
                     struct prism2_hostapd_param *param)
{
	islpci_private *priv = netdev_priv(ndev);
	struct iw_request_info info;
	int i, rvalue;
	struct obj_bsslist *bsslist;
	u32 noise = 0;
	char *extra = "";
	char *current_ev = "foo";
	union oid_res_t r;

	if (islpci_get_state(priv) < PRV_STATE_INIT) {
		/* device is not ready, fail gently */
		return 0;
	}

	/* first get the noise value. We will use it to report the link quality */
	rvalue = mgt_get_request(priv, DOT11_OID_NOISEFLOOR, 0, NULL, &r);
	noise = r.u;

	/* Ask the device for a list of known bss. We can report at most
	 * IW_MAX_AP=64 to the range struct. But the device won't repport anything
	 * if you change the value of IWMAX_BSS=24.
	 */
	rvalue |= mgt_get_request(priv, DOT11_OID_BSSLIST, 0, NULL, &r);
	bsslist = r.ptr;

	info.cmd = PRISM54_HOSTAPD;
	info.flags = 0;

	/* ok now, scan the list and translate its info */
	for (i = 0; i < min(IW_MAX_AP, (int) bsslist->nr); i++)
		current_ev = prism54_translate_bss(ndev, &info, current_ev,
						   extra + IW_SCAN_MAX_DATA,
						   &(bsslist->bsslist[i]),
						   noise);
	kfree(bsslist);

	return rvalue;
}