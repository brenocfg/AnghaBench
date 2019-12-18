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
union oid_res_t {int u; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
typedef  int /*<<< orphan*/  islpci_private ;

/* Variables and functions */
 int /*<<< orphan*/  IFNAMSIZ ; 
#define  INL_PHYCAP_2400MHZ 130 
#define  INL_PHYCAP_5000MHZ 129 
#define  INL_PHYCAP_FAA 128 
 int /*<<< orphan*/  OID_INL_PHYCAPABILITIES ; 
 scalar_t__ PRV_STATE_INIT ; 
 scalar_t__ islpci_get_state (int /*<<< orphan*/ *) ; 
 int mgt_get_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,union oid_res_t*) ; 
 int /*<<< orphan*/ * netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
prism54_get_name(struct net_device *ndev, struct iw_request_info *info,
		 char *cwrq, char *extra)
{
	islpci_private *priv = netdev_priv(ndev);
	char *capabilities;
	union oid_res_t r;
	int rvalue;

	if (islpci_get_state(priv) < PRV_STATE_INIT) {
		strncpy(cwrq, "NOT READY!", IFNAMSIZ);
		return 0;
	}
	rvalue = mgt_get_request(priv, OID_INL_PHYCAPABILITIES, 0, NULL, &r);

	switch (r.u) {
	case INL_PHYCAP_5000MHZ:
		capabilities = "IEEE 802.11a/b/g";
		break;
	case INL_PHYCAP_FAA:
		capabilities = "IEEE 802.11b/g - FAA Support";
		break;
	case INL_PHYCAP_2400MHZ:
	default:
		capabilities = "IEEE 802.11b/g";	/* Default */
		break;
	}
	strncpy(cwrq, capabilities, IFNAMSIZ);
	return rvalue;
}