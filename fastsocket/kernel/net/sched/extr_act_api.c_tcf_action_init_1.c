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
struct tc_action_ops {int (* init ) (struct nlattr*,struct nlattr*,struct tc_action*,int,int) ;int /*<<< orphan*/  owner; } ;
struct tc_action {struct tc_action_ops* ops; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int ACT_P_CREATED ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 struct tc_action* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IFNAMSIZ ; 
 size_t TCA_ACT_KIND ; 
 int /*<<< orphan*/  TCA_ACT_MAX ; 
 size_t TCA_ACT_OPTIONS ; 
 int /*<<< orphan*/  kfree (struct tc_action*) ; 
 struct tc_action* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ *) ; 
 int nla_strlcpy (char*,struct nlattr*,int) ; 
 int /*<<< orphan*/  request_module (char*,char*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int strlcpy (char*,char*,int) ; 
 int stub1 (struct nlattr*,struct nlattr*,struct tc_action*,int,int) ; 
 int stub2 (struct nlattr*,struct nlattr*,struct tc_action*,int,int) ; 
 struct tc_action_ops* tc_lookup_action_n (char*) ; 

struct tc_action *tcf_action_init_1(struct nlattr *nla, struct nlattr *est,
				    char *name, int ovr, int bind)
{
	struct tc_action *a;
	struct tc_action_ops *a_o;
	char act_name[IFNAMSIZ];
	struct nlattr *tb[TCA_ACT_MAX+1];
	struct nlattr *kind;
	int err;

	if (name == NULL) {
		err = nla_parse_nested(tb, TCA_ACT_MAX, nla, NULL);
		if (err < 0)
			goto err_out;
		err = -EINVAL;
		kind = tb[TCA_ACT_KIND];
		if (kind == NULL)
			goto err_out;
		if (nla_strlcpy(act_name, kind, IFNAMSIZ) >= IFNAMSIZ)
			goto err_out;
	} else {
		err = -EINVAL;
		if (strlcpy(act_name, name, IFNAMSIZ) >= IFNAMSIZ)
			goto err_out;
	}

	a_o = tc_lookup_action_n(act_name);
	if (a_o == NULL) {
#ifdef CONFIG_MODULES
		rtnl_unlock();
		request_module("act_%s", act_name);
		rtnl_lock();

		a_o = tc_lookup_action_n(act_name);

		/* We dropped the RTNL semaphore in order to
		 * perform the module load.  So, even if we
		 * succeeded in loading the module we have to
		 * tell the caller to replay the request.  We
		 * indicate this using -EAGAIN.
		 */
		if (a_o != NULL) {
			err = -EAGAIN;
			goto err_mod;
		}
#endif
		err = -ENOENT;
		goto err_out;
	}

	err = -ENOMEM;
	a = kzalloc(sizeof(*a), GFP_KERNEL);
	if (a == NULL)
		goto err_mod;

	/* backward compatibility for policer */
	if (name == NULL)
		err = a_o->init(tb[TCA_ACT_OPTIONS], est, a, ovr, bind);
	else
		err = a_o->init(nla, est, a, ovr, bind);
	if (err < 0)
		goto err_free;

	/* module count goes up only when brand new policy is created
	   if it exists and is only bound to in a_o->init() then
	   ACT_P_CREATED is not returned (a zero is).
	*/
	if (err != ACT_P_CREATED)
		module_put(a_o->owner);
	a->ops = a_o;

	return a;

err_free:
	kfree(a);
err_mod:
	module_put(a_o->owner);
err_out:
	return ERR_PTR(err);
}