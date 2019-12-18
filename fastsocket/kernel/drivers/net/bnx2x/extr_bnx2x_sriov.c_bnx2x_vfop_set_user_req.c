#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  vlan; } ;
struct TYPE_4__ {int /*<<< orphan*/  mac; } ;
struct TYPE_6__ {TYPE_2__ vlan; TYPE_1__ mac; } ;
struct bnx2x_vlan_mac_data {TYPE_3__ u; int /*<<< orphan*/  cmd; } ;
struct bnx2x_vfop_filter {int type; int /*<<< orphan*/  vid; int /*<<< orphan*/  mac; scalar_t__ add; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
#define  BNX2X_VFOP_FILTER_MAC 129 
#define  BNX2X_VFOP_FILTER_VLAN 128 
 int /*<<< orphan*/  BNX2X_VLAN_MAC_ADD ; 
 int /*<<< orphan*/  BNX2X_VLAN_MAC_DEL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnx2x_vfop_set_user_req(struct bnx2x *bp,
				    struct bnx2x_vfop_filter *pos,
				    struct bnx2x_vlan_mac_data *user_req)
{
	user_req->cmd = pos->add ? BNX2X_VLAN_MAC_ADD :
		BNX2X_VLAN_MAC_DEL;

	switch (pos->type) {
	case BNX2X_VFOP_FILTER_MAC:
		memcpy(user_req->u.mac.mac, pos->mac, ETH_ALEN);
		break;
	case BNX2X_VFOP_FILTER_VLAN:
		user_req->u.vlan.vlan = pos->vid;
		break;
	default:
		BNX2X_ERR("Invalid filter type, skipping\n");
		return 1;
	}
	return 0;
}