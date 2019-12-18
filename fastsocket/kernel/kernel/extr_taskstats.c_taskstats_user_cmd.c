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
typedef  int /*<<< orphan*/  u32 ;
struct taskstats {int dummy; } ;
struct sk_buff {int dummy; } ;
struct genl_info {scalar_t__* attrs; int /*<<< orphan*/  snd_pid; } ;
typedef  int /*<<< orphan*/  cpumask_var_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEREGISTER ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  REGISTER ; 
 size_t TASKSTATS_CMD_ATTR_DEREGISTER_CPUMASK ; 
 size_t TASKSTATS_CMD_ATTR_PID ; 
 size_t TASKSTATS_CMD_ATTR_REGISTER_CPUMASK ; 
 size_t TASKSTATS_CMD_ATTR_TGID ; 
 int /*<<< orphan*/  TASKSTATS_CMD_NEW ; 
 int /*<<< orphan*/  TASKSTATS_TYPE_PID ; 
 int /*<<< orphan*/  TASKSTATS_TYPE_TGID ; 
 int add_del_listener (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int fill_pid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct taskstats*) ; 
 int fill_tgid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct taskstats*) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 struct taskstats* mk_reply (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u32 (scalar_t__) ; 
 size_t nla_total_size (int) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 int parse (scalar_t__,int /*<<< orphan*/ ) ; 
 int prepare_reply (struct genl_info*,int /*<<< orphan*/ ,struct sk_buff**,size_t) ; 
 int send_reply (struct sk_buff*,struct genl_info*) ; 

__attribute__((used)) static int taskstats_user_cmd(struct sk_buff *skb, struct genl_info *info)
{
	int rc;
	struct sk_buff *rep_skb;
	struct taskstats *stats;
	size_t size;
	cpumask_var_t mask;

	if (!alloc_cpumask_var(&mask, GFP_KERNEL))
		return -ENOMEM;

	rc = parse(info->attrs[TASKSTATS_CMD_ATTR_REGISTER_CPUMASK], mask);
	if (rc < 0)
		goto free_return_rc;
	if (rc == 0) {
		rc = add_del_listener(info->snd_pid, mask, REGISTER);
		goto free_return_rc;
	}

	rc = parse(info->attrs[TASKSTATS_CMD_ATTR_DEREGISTER_CPUMASK], mask);
	if (rc < 0)
		goto free_return_rc;
	if (rc == 0) {
		rc = add_del_listener(info->snd_pid, mask, DEREGISTER);
free_return_rc:
		free_cpumask_var(mask);
		return rc;
	}
	free_cpumask_var(mask);

	/*
	 * Size includes space for nested attributes
	 */
	size = nla_total_size(sizeof(u32)) +
		nla_total_size(sizeof(struct taskstats)) + nla_total_size(0);

	rc = prepare_reply(info, TASKSTATS_CMD_NEW, &rep_skb, size);
	if (rc < 0)
		return rc;

	rc = -EINVAL;
	if (info->attrs[TASKSTATS_CMD_ATTR_PID]) {
		u32 pid = nla_get_u32(info->attrs[TASKSTATS_CMD_ATTR_PID]);
		stats = mk_reply(rep_skb, TASKSTATS_TYPE_PID, pid);
		if (!stats)
			goto err;

		rc = fill_pid(pid, NULL, stats);
		if (rc < 0)
			goto err;
	} else if (info->attrs[TASKSTATS_CMD_ATTR_TGID]) {
		u32 tgid = nla_get_u32(info->attrs[TASKSTATS_CMD_ATTR_TGID]);
		stats = mk_reply(rep_skb, TASKSTATS_TYPE_TGID, tgid);
		if (!stats)
			goto err;

		rc = fill_tgid(tgid, NULL, stats);
		if (rc < 0)
			goto err;
	} else
		goto err;

	return send_reply(rep_skb, info);
err:
	nlmsg_free(rep_skb);
	return rc;
}