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
struct tcf_mirred {int tcfm_ok_push; int /*<<< orphan*/  tcfm_list; int /*<<< orphan*/  tcf_lock; struct net_device* tcfm_dev; scalar_t__ tcfm_ifindex; int /*<<< orphan*/  tcfm_eaction; int /*<<< orphan*/  tcf_action; } ;
struct tcf_common {int dummy; } ;
struct tc_mirred {scalar_t__ ifindex; int /*<<< orphan*/  eaction; int /*<<< orphan*/  action; int /*<<< orphan*/  index; } ;
struct tc_action {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {int type; } ;

/* Variables and functions */
 int ACT_P_CREATED ; 
#define  ARPHRD_IPGRE 133 
#define  ARPHRD_NONE 132 
#define  ARPHRD_SIT 131 
#define  ARPHRD_TUNNEL 130 
#define  ARPHRD_TUNNEL6 129 
#define  ARPHRD_VOID 128 
 int EEXIST ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct tcf_common*) ; 
 int PTR_ERR (struct tcf_common*) ; 
 int /*<<< orphan*/  TCA_MIRRED_MAX ; 
 size_t TCA_MIRRED_PARMS ; 
 struct net_device* __dev_get_by_index (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mirred_hash_info ; 
 int /*<<< orphan*/  mirred_idx_gen ; 
 int /*<<< orphan*/  mirred_list ; 
 int /*<<< orphan*/  mirred_policy ; 
 struct tc_mirred* nla_data (struct nlattr*) ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct tcf_common* tcf_hash_check (int /*<<< orphan*/ ,struct tc_action*,int,int /*<<< orphan*/ *) ; 
 struct tcf_common* tcf_hash_create (int /*<<< orphan*/ ,struct nlattr*,struct tc_action*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_hash_insert (struct tcf_common*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_mirred_release (struct tcf_mirred*,int) ; 
 struct tcf_mirred* to_mirred (struct tcf_common*) ; 

__attribute__((used)) static int tcf_mirred_init(struct nlattr *nla, struct nlattr *est,
			   struct tc_action *a, int ovr, int bind)
{
	struct nlattr *tb[TCA_MIRRED_MAX + 1];
	struct tc_mirred *parm;
	struct tcf_mirred *m;
	struct tcf_common *pc;
	struct net_device *dev = NULL;
	int ret = 0, err;
	int ok_push = 0;

	if (nla == NULL)
		return -EINVAL;

	err = nla_parse_nested(tb, TCA_MIRRED_MAX, nla, mirred_policy);
	if (err < 0)
		return err;

	if (tb[TCA_MIRRED_PARMS] == NULL)
		return -EINVAL;
	parm = nla_data(tb[TCA_MIRRED_PARMS]);

	if (parm->ifindex) {
		dev = __dev_get_by_index(&init_net, parm->ifindex);
		if (dev == NULL)
			return -ENODEV;
		switch (dev->type) {
			case ARPHRD_TUNNEL:
			case ARPHRD_TUNNEL6:
			case ARPHRD_SIT:
			case ARPHRD_IPGRE:
			case ARPHRD_VOID:
			case ARPHRD_NONE:
				ok_push = 0;
				break;
			default:
				ok_push = 1;
				break;
		}
	}

	pc = tcf_hash_check(parm->index, a, bind, &mirred_hash_info);
	if (!pc) {
		if (!parm->ifindex)
			return -EINVAL;
		pc = tcf_hash_create(parm->index, est, a, sizeof(*m), bind,
				     &mirred_idx_gen, &mirred_hash_info);
		if (IS_ERR(pc))
		    return PTR_ERR(pc);
		ret = ACT_P_CREATED;
	} else {
		if (!ovr) {
			tcf_mirred_release(to_mirred(pc), bind);
			return -EEXIST;
		}
	}
	m = to_mirred(pc);

	spin_lock_bh(&m->tcf_lock);
	m->tcf_action = parm->action;
	m->tcfm_eaction = parm->eaction;
	if (parm->ifindex) {
		m->tcfm_ifindex = parm->ifindex;
		if (ret != ACT_P_CREATED)
			dev_put(m->tcfm_dev);
		m->tcfm_dev = dev;
		dev_hold(dev);
		m->tcfm_ok_push = ok_push;
	}
	spin_unlock_bh(&m->tcf_lock);
	if (ret == ACT_P_CREATED) {
		list_add(&m->tcfm_list, &mirred_list);
		tcf_hash_insert(pc, &mirred_hash_info);
	}

	return ret;
}