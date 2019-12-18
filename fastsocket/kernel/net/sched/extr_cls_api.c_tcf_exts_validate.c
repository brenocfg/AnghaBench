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
struct tcf_proto {int dummy; } ;
struct tcf_exts {struct tc_action* action; } ;
struct tcf_ext_map {size_t police; size_t action; } ;
struct tc_action {int /*<<< orphan*/  type; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct tc_action*) ; 
 int PTR_ERR (struct tc_action*) ; 
 int /*<<< orphan*/  TCA_ACT_BIND ; 
 int /*<<< orphan*/  TCA_ACT_NOREPLACE ; 
 int /*<<< orphan*/  TCA_OLD_COMPAT ; 
 int /*<<< orphan*/  memset (struct tcf_exts*,int /*<<< orphan*/ ,int) ; 
 struct tc_action* tcf_action_init (struct nlattr*,struct nlattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tc_action* tcf_action_init_1 (struct nlattr*,struct nlattr*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tcf_exts_validate(struct tcf_proto *tp, struct nlattr **tb,
		  struct nlattr *rate_tlv, struct tcf_exts *exts,
		  const struct tcf_ext_map *map)
{
	memset(exts, 0, sizeof(*exts));

#ifdef CONFIG_NET_CLS_ACT
	{
		struct tc_action *act;

		if (map->police && tb[map->police]) {
			act = tcf_action_init_1(tb[map->police], rate_tlv,
						"police", TCA_ACT_NOREPLACE,
						TCA_ACT_BIND);
			if (IS_ERR(act))
				return PTR_ERR(act);

			act->type = TCA_OLD_COMPAT;
			exts->action = act;
		} else if (map->action && tb[map->action]) {
			act = tcf_action_init(tb[map->action], rate_tlv, NULL,
					      TCA_ACT_NOREPLACE, TCA_ACT_BIND);
			if (IS_ERR(act))
				return PTR_ERR(act);

			exts->action = act;
		}
	}
#else
	if ((map->action && tb[map->action]) ||
	    (map->police && tb[map->police]))
		return -EOPNOTSUPP;
#endif

	return 0;
}