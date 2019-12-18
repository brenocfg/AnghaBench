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
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct genl_info {struct nlattr** attrs; } ;
struct file {int /*<<< orphan*/  f_dentry; } ;
struct cgroupstats {int dummy; } ;

/* Variables and functions */
 size_t CGROUPSTATS_CMD_ATTR_FD ; 
 int /*<<< orphan*/  CGROUPSTATS_CMD_NEW ; 
 int /*<<< orphan*/  CGROUPSTATS_TYPE_CGROUP_STATS ; 
 int EINVAL ; 
 int cgroupstats_build (struct cgroupstats*,int /*<<< orphan*/ ) ; 
 struct file* fget_light (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  fput_light (struct file*,int) ; 
 int /*<<< orphan*/  memset (struct cgroupstats*,int /*<<< orphan*/ ,int) ; 
 struct cgroupstats* nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 struct nlattr* nla_reserve (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 size_t nla_total_size (int) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 int prepare_reply (struct genl_info*,int /*<<< orphan*/ ,struct sk_buff**,size_t) ; 
 int send_reply (struct sk_buff*,struct genl_info*) ; 

__attribute__((used)) static int cgroupstats_user_cmd(struct sk_buff *skb, struct genl_info *info)
{
	int rc = 0;
	struct sk_buff *rep_skb;
	struct cgroupstats *stats;
	struct nlattr *na;
	size_t size;
	u32 fd;
	struct file *file;
	int fput_needed;

	na = info->attrs[CGROUPSTATS_CMD_ATTR_FD];
	if (!na)
		return -EINVAL;

	fd = nla_get_u32(info->attrs[CGROUPSTATS_CMD_ATTR_FD]);
	file = fget_light(fd, &fput_needed);
	if (!file)
		return 0;

	size = nla_total_size(sizeof(struct cgroupstats));

	rc = prepare_reply(info, CGROUPSTATS_CMD_NEW, &rep_skb,
				size);
	if (rc < 0)
		goto err;

	na = nla_reserve(rep_skb, CGROUPSTATS_TYPE_CGROUP_STATS,
				sizeof(struct cgroupstats));
	stats = nla_data(na);
	memset(stats, 0, sizeof(*stats));

	rc = cgroupstats_build(stats, file->f_dentry);
	if (rc < 0) {
		nlmsg_free(rep_skb);
		goto err;
	}

	rc = send_reply(rep_skb, info);

err:
	fput_light(file, fput_needed);
	return rc;
}