#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct vport {int /*<<< orphan*/  upcall_pid; TYPE_1__* ops; int /*<<< orphan*/  port_no; int /*<<< orphan*/  dp; } ;
struct sk_buff {int dummy; } ;
struct ovs_vport_stats {int dummy; } ;
struct ovs_header {int /*<<< orphan*/  dp_ifindex; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_name ) (struct vport*) ;int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  OVS_VPORT_ATTR_NAME ; 
 int /*<<< orphan*/  OVS_VPORT_ATTR_PORT_NO ; 
 int /*<<< orphan*/  OVS_VPORT_ATTR_STATS ; 
 int /*<<< orphan*/  OVS_VPORT_ATTR_TYPE ; 
 int /*<<< orphan*/  OVS_VPORT_ATTR_UPCALL_PID ; 
 int /*<<< orphan*/  dp_vport_genl_family ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,struct ovs_header*) ; 
 int genlmsg_end (struct sk_buff*,struct ovs_header*) ; 
 struct ovs_header* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_dpifindex (int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct ovs_vport_stats*) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ovs_vport_get_options (struct vport*,struct sk_buff*) ; 
 int /*<<< orphan*/  ovs_vport_get_stats (struct vport*,struct ovs_vport_stats*) ; 
 int /*<<< orphan*/  stub1 (struct vport*) ; 

__attribute__((used)) static int ovs_vport_cmd_fill_info(struct vport *vport, struct sk_buff *skb,
				   u32 pid, u32 seq, u32 flags, u8 cmd)
{
	struct ovs_header *ovs_header;
	struct ovs_vport_stats vport_stats;
	int err;

	ovs_header = genlmsg_put(skb, pid, seq, &dp_vport_genl_family,
				 flags, cmd);
	if (!ovs_header)
		return -EMSGSIZE;

	ovs_header->dp_ifindex = get_dpifindex(vport->dp);

	if (nla_put_u32(skb, OVS_VPORT_ATTR_PORT_NO, vport->port_no) ||
	    nla_put_u32(skb, OVS_VPORT_ATTR_TYPE, vport->ops->type) ||
	    nla_put_string(skb, OVS_VPORT_ATTR_NAME, vport->ops->get_name(vport)) ||
	    nla_put_u32(skb, OVS_VPORT_ATTR_UPCALL_PID, vport->upcall_pid))
		goto nla_put_failure;

	ovs_vport_get_stats(vport, &vport_stats);
	if (nla_put(skb, OVS_VPORT_ATTR_STATS, sizeof(struct ovs_vport_stats),
		    &vport_stats))
		goto nla_put_failure;

	err = ovs_vport_get_options(vport, skb);
	if (err == -EMSGSIZE)
		goto error;

	return genlmsg_end(skb, ovs_header);

nla_put_failure:
	err = -EMSGSIZE;
error:
	genlmsg_cancel(skb, ovs_header);
	return err;
}