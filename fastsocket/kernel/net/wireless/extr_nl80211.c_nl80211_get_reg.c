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
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct ieee80211_regdomain {unsigned int n_reg_rules; struct ieee80211_reg_rule* reg_rules; scalar_t__ dfs_region; int /*<<< orphan*/  alpha2; } ;
struct ieee80211_power_rule {int /*<<< orphan*/  max_eirp; int /*<<< orphan*/  max_antenna_gain; } ;
struct ieee80211_freq_range {int /*<<< orphan*/  max_bandwidth_khz; int /*<<< orphan*/  end_freq_khz; int /*<<< orphan*/  start_freq_khz; } ;
struct ieee80211_reg_rule {int /*<<< orphan*/  flags; struct ieee80211_power_rule power_rule; struct ieee80211_freq_range freq_range; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_pid; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NL80211_ATTR_DFS_REGION ; 
 int /*<<< orphan*/  NL80211_ATTR_FREQ_RANGE_END ; 
 int /*<<< orphan*/  NL80211_ATTR_FREQ_RANGE_MAX_BW ; 
 int /*<<< orphan*/  NL80211_ATTR_FREQ_RANGE_START ; 
 int /*<<< orphan*/  NL80211_ATTR_POWER_RULE_MAX_ANT_GAIN ; 
 int /*<<< orphan*/  NL80211_ATTR_POWER_RULE_MAX_EIRP ; 
 int /*<<< orphan*/  NL80211_ATTR_REG_ALPHA2 ; 
 unsigned int NL80211_ATTR_REG_RULES ; 
 int /*<<< orphan*/  NL80211_ATTR_REG_RULE_FLAGS ; 
 int /*<<< orphan*/  NL80211_ATTR_USER_REG_HINT_TYPE ; 
 int /*<<< orphan*/  NL80211_CMD_GET_REG ; 
 int /*<<< orphan*/  NL80211_USER_REG_HINT_CELL_BASE ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  cfg80211_mutex ; 
 int /*<<< orphan*/  cfg80211_regdomain ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 void* nl80211hdr_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,unsigned int) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ieee80211_regdomain* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ reg_last_request_cell_base () ; 

__attribute__((used)) static int nl80211_get_reg(struct sk_buff *skb, struct genl_info *info)
{
	const struct ieee80211_regdomain *regdom;
	struct sk_buff *msg;
	void *hdr = NULL;
	struct nlattr *nl_reg_rules;
	unsigned int i;
	int err = -EINVAL;

	mutex_lock(&cfg80211_mutex);

	if (!cfg80211_regdomain)
		goto out;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg) {
		err = -ENOBUFS;
		goto out;
	}

	hdr = nl80211hdr_put(msg, info->snd_pid, info->snd_seq, 0,
			     NL80211_CMD_GET_REG);
	if (!hdr)
		goto put_failure;

	if (reg_last_request_cell_base() &&
	    nla_put_u32(msg, NL80211_ATTR_USER_REG_HINT_TYPE,
			NL80211_USER_REG_HINT_CELL_BASE))
		goto nla_put_failure;

	rcu_read_lock();
	regdom = rcu_dereference(cfg80211_regdomain);

	if (nla_put_string(msg, NL80211_ATTR_REG_ALPHA2, regdom->alpha2) ||
	    (regdom->dfs_region &&
	     nla_put_u8(msg, NL80211_ATTR_DFS_REGION, regdom->dfs_region)))
		goto nla_put_failure_rcu;

	nl_reg_rules = nla_nest_start(msg, NL80211_ATTR_REG_RULES);
	if (!nl_reg_rules)
		goto nla_put_failure_rcu;

	for (i = 0; i < regdom->n_reg_rules; i++) {
		struct nlattr *nl_reg_rule;
		const struct ieee80211_reg_rule *reg_rule;
		const struct ieee80211_freq_range *freq_range;
		const struct ieee80211_power_rule *power_rule;

		reg_rule = &regdom->reg_rules[i];
		freq_range = &reg_rule->freq_range;
		power_rule = &reg_rule->power_rule;

		nl_reg_rule = nla_nest_start(msg, i);
		if (!nl_reg_rule)
			goto nla_put_failure_rcu;

		if (nla_put_u32(msg, NL80211_ATTR_REG_RULE_FLAGS,
				reg_rule->flags) ||
		    nla_put_u32(msg, NL80211_ATTR_FREQ_RANGE_START,
				freq_range->start_freq_khz) ||
		    nla_put_u32(msg, NL80211_ATTR_FREQ_RANGE_END,
				freq_range->end_freq_khz) ||
		    nla_put_u32(msg, NL80211_ATTR_FREQ_RANGE_MAX_BW,
				freq_range->max_bandwidth_khz) ||
		    nla_put_u32(msg, NL80211_ATTR_POWER_RULE_MAX_ANT_GAIN,
				power_rule->max_antenna_gain) ||
		    nla_put_u32(msg, NL80211_ATTR_POWER_RULE_MAX_EIRP,
				power_rule->max_eirp))
			goto nla_put_failure_rcu;

		nla_nest_end(msg, nl_reg_rule);
	}
	rcu_read_unlock();

	nla_nest_end(msg, nl_reg_rules);

	genlmsg_end(msg, hdr);
	err = genlmsg_reply(msg, info);
	goto out;

nla_put_failure_rcu:
	rcu_read_unlock();
nla_put_failure:
	genlmsg_cancel(msg, hdr);
put_failure:
	nlmsg_free(msg);
	err = -EMSGSIZE;
out:
	mutex_unlock(&cfg80211_mutex);
	return err;
}