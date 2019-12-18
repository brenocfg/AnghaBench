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
typedef  int /*<<< orphan*/  u32 ;
struct tc_action {TYPE_1__* ops; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
typedef  int /*<<< orphan*/  index ;
struct TYPE_2__ {scalar_t__ (* lookup ) (struct tc_action*,int) ;int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 struct tc_action* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t TCA_ACT_INDEX ; 
 size_t TCA_ACT_KIND ; 
 int /*<<< orphan*/  TCA_ACT_MAX ; 
 int /*<<< orphan*/  kfree (struct tc_action*) ; 
 struct tc_action* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int nla_get_u32 (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct tc_action*,int) ; 
 TYPE_1__* tc_lookup_action (struct nlattr*) ; 

__attribute__((used)) static struct tc_action *
tcf_action_get_1(struct nlattr *nla, struct nlmsghdr *n, u32 pid)
{
	struct nlattr *tb[TCA_ACT_MAX+1];
	struct tc_action *a;
	int index;
	int err;

	err = nla_parse_nested(tb, TCA_ACT_MAX, nla, NULL);
	if (err < 0)
		goto err_out;

	err = -EINVAL;
	if (tb[TCA_ACT_INDEX] == NULL ||
	    nla_len(tb[TCA_ACT_INDEX]) < sizeof(index))
		goto err_out;
	index = nla_get_u32(tb[TCA_ACT_INDEX]);

	err = -ENOMEM;
	a = kzalloc(sizeof(struct tc_action), GFP_KERNEL);
	if (a == NULL)
		goto err_out;

	err = -EINVAL;
	a->ops = tc_lookup_action(tb[TCA_ACT_KIND]);
	if (a->ops == NULL)
		goto err_free;
	if (a->ops->lookup == NULL)
		goto err_mod;
	err = -ENOENT;
	if (a->ops->lookup(a, index) == 0)
		goto err_mod;

	module_put(a->ops->owner);
	return a;

err_mod:
	module_put(a->ops->owner);
err_free:
	kfree(a);
err_out:
	return ERR_PTR(err);
}