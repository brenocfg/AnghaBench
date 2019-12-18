#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vport {struct datapath* dp; } ;
struct sk_buff {int dummy; } ;
struct datapath {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  genl_sock; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  OVS_VPORT_CMD_DEL ; 
 int /*<<< orphan*/  PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  genlmsg_multicast_netns (TYPE_2__*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netlink_set_err (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovs_dp_detach_port (struct vport*) ; 
 TYPE_2__* ovs_dp_get_net (struct datapath*) ; 
 TYPE_1__ ovs_dp_vport_multicast_group ; 
 struct sk_buff* ovs_vport_cmd_build_info (struct vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dp_detach_port_notify(struct vport *vport)
{
	struct sk_buff *notify;
	struct datapath *dp;

	dp = vport->dp;
	notify = ovs_vport_cmd_build_info(vport, 0, 0,
					  OVS_VPORT_CMD_DEL);
	ovs_dp_detach_port(vport);
	if (IS_ERR(notify)) {
		netlink_set_err(ovs_dp_get_net(dp)->genl_sock, 0,
				ovs_dp_vport_multicast_group.id,
				PTR_ERR(notify));
		return;
	}

	genlmsg_multicast_netns(ovs_dp_get_net(dp), notify, 0,
				ovs_dp_vport_multicast_group.id,
				GFP_KERNEL);
}