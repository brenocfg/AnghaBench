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
struct vport {int /*<<< orphan*/  sk; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct ovs_header {int dummy; } ;
struct nlattr {int dummy; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_pid; struct ovs_header* userhdr; struct nlattr** attrs; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct vport*) ; 
 int /*<<< orphan*/  OVS_VPORT_CMD_NEW ; 
 int PTR_ERR (struct vport*) ; 
 int genlmsg_reply (struct vport*,struct genl_info*) ; 
 struct vport* lookup_vport (int /*<<< orphan*/ ,struct ovs_header*,struct nlattr**) ; 
 struct vport* ovs_vport_cmd_build_info (struct vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovs_vport_cmd_get(struct sk_buff *skb, struct genl_info *info)
{
	struct nlattr **a = info->attrs;
	struct ovs_header *ovs_header = info->userhdr;
	struct sk_buff *reply;
	struct vport *vport;
	int err;

	rcu_read_lock();
	vport = lookup_vport(sock_net(skb->sk), ovs_header, a);
	err = PTR_ERR(vport);
	if (IS_ERR(vport))
		goto exit_unlock;

	reply = ovs_vport_cmd_build_info(vport, info->snd_pid,
					 info->snd_seq, OVS_VPORT_CMD_NEW);
	err = PTR_ERR(reply);
	if (IS_ERR(reply))
		goto exit_unlock;

	rcu_read_unlock();

	return genlmsg_reply(reply, info);

exit_unlock:
	rcu_read_unlock();
	return err;
}