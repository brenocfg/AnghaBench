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
struct vport {scalar_t__ upcall_pid; TYPE_1__* ops; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlattr {int dummy; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_pid; int /*<<< orphan*/  userhdr; struct nlattr** attrs; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct vport*) ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 size_t OVS_VPORT_ATTR_OPTIONS ; 
 size_t OVS_VPORT_ATTR_TYPE ; 
 size_t OVS_VPORT_ATTR_UPCALL_PID ; 
 int /*<<< orphan*/  OVS_VPORT_CMD_NEW ; 
 int PTR_ERR (struct vport*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct vport* lookup_vport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nlattr**) ; 
 scalar_t__ nla_get_u32 (struct nlattr*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovs_dp_vport_multicast_group ; 
 int /*<<< orphan*/  ovs_lock () ; 
 int /*<<< orphan*/  ovs_notify (struct sk_buff*,struct genl_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ovs_unlock () ; 
 int ovs_vport_cmd_fill_info (struct vport*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ovs_vport_set_options (struct vport*,struct nlattr*) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovs_vport_cmd_set(struct sk_buff *skb, struct genl_info *info)
{
	struct nlattr **a = info->attrs;
	struct sk_buff *reply;
	struct vport *vport;
	int err;

	ovs_lock();
	vport = lookup_vport(sock_net(skb->sk), info->userhdr, a);
	err = PTR_ERR(vport);
	if (IS_ERR(vport))
		goto exit_unlock;

	if (a[OVS_VPORT_ATTR_TYPE] &&
	    nla_get_u32(a[OVS_VPORT_ATTR_TYPE]) != vport->ops->type) {
		err = -EINVAL;
		goto exit_unlock;
	}

	reply = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!reply) {
		err = -ENOMEM;
		goto exit_unlock;
	}

	if (a[OVS_VPORT_ATTR_OPTIONS]) {
		err = ovs_vport_set_options(vport, a[OVS_VPORT_ATTR_OPTIONS]);
		if (err)
			goto exit_free;
	}

	if (a[OVS_VPORT_ATTR_UPCALL_PID])
		vport->upcall_pid = nla_get_u32(a[OVS_VPORT_ATTR_UPCALL_PID]);

	err = ovs_vport_cmd_fill_info(vport, reply, info->snd_pid,
				      info->snd_seq, 0, OVS_VPORT_CMD_NEW);
	BUG_ON(err < 0);

	ovs_unlock();
	ovs_notify(reply, info, &ovs_dp_vport_multicast_group);
	return 0;

exit_free:
	kfree_skb(reply);
exit_unlock:
	ovs_unlock();
	return err;
}