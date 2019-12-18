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
typedef  int u32 ;
struct vport_parms {int port_no; void* upcall_pid; struct datapath* dp; struct nlattr* options; void* type; int /*<<< orphan*/  name; } ;
struct vport {int /*<<< orphan*/  sk; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct ovs_header {int /*<<< orphan*/  dp_ifindex; } ;
struct nlattr {int dummy; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_pid; struct ovs_header* userhdr; struct nlattr** attrs; } ;
struct datapath {int dummy; } ;

/* Variables and functions */
 int DP_MAX_PORTS ; 
 int EBUSY ; 
 int EFBIG ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct vport*) ; 
 size_t OVS_VPORT_ATTR_NAME ; 
 size_t OVS_VPORT_ATTR_OPTIONS ; 
 size_t OVS_VPORT_ATTR_PORT_NO ; 
 size_t OVS_VPORT_ATTR_TYPE ; 
 size_t OVS_VPORT_ATTR_UPCALL_PID ; 
 int /*<<< orphan*/  OVS_VPORT_CMD_NEW ; 
 int PTR_ERR (struct vport*) ; 
 struct datapath* get_dp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vport* new_vport (struct vport_parms*) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 void* nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  ovs_dp_detach_port (struct vport*) ; 
 int /*<<< orphan*/  ovs_dp_vport_multicast_group ; 
 int /*<<< orphan*/  ovs_lock () ; 
 int /*<<< orphan*/  ovs_notify (struct vport*,struct genl_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ovs_unlock () ; 
 struct vport* ovs_vport_cmd_build_info (struct vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vport* ovs_vport_ovsl (struct datapath*,int) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovs_vport_cmd_new(struct sk_buff *skb, struct genl_info *info)
{
	struct nlattr **a = info->attrs;
	struct ovs_header *ovs_header = info->userhdr;
	struct vport_parms parms;
	struct sk_buff *reply;
	struct vport *vport;
	struct datapath *dp;
	u32 port_no;
	int err;

	err = -EINVAL;
	if (!a[OVS_VPORT_ATTR_NAME] || !a[OVS_VPORT_ATTR_TYPE] ||
	    !a[OVS_VPORT_ATTR_UPCALL_PID])
		goto exit;

	ovs_lock();
	dp = get_dp(sock_net(skb->sk), ovs_header->dp_ifindex);
	err = -ENODEV;
	if (!dp)
		goto exit_unlock;

	if (a[OVS_VPORT_ATTR_PORT_NO]) {
		port_no = nla_get_u32(a[OVS_VPORT_ATTR_PORT_NO]);

		err = -EFBIG;
		if (port_no >= DP_MAX_PORTS)
			goto exit_unlock;

		vport = ovs_vport_ovsl(dp, port_no);
		err = -EBUSY;
		if (vport)
			goto exit_unlock;
	} else {
		for (port_no = 1; ; port_no++) {
			if (port_no >= DP_MAX_PORTS) {
				err = -EFBIG;
				goto exit_unlock;
			}
			vport = ovs_vport_ovsl(dp, port_no);
			if (!vport)
				break;
		}
	}

	parms.name = nla_data(a[OVS_VPORT_ATTR_NAME]);
	parms.type = nla_get_u32(a[OVS_VPORT_ATTR_TYPE]);
	parms.options = a[OVS_VPORT_ATTR_OPTIONS];
	parms.dp = dp;
	parms.port_no = port_no;
	parms.upcall_pid = nla_get_u32(a[OVS_VPORT_ATTR_UPCALL_PID]);

	vport = new_vport(&parms);
	err = PTR_ERR(vport);
	if (IS_ERR(vport))
		goto exit_unlock;

	err = 0;
	reply = ovs_vport_cmd_build_info(vport, info->snd_pid, info->snd_seq,
					 OVS_VPORT_CMD_NEW);
	if (IS_ERR(reply)) {
		err = PTR_ERR(reply);
		ovs_dp_detach_port(vport);
		goto exit_unlock;
	}

	ovs_notify(reply, info, &ovs_dp_vport_multicast_group);

exit_unlock:
	ovs_unlock();
exit:
	return err;
}