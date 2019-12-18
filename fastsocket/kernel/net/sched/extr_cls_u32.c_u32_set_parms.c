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
typedef  void* u32 ;
struct tcf_proto {int dummy; } ;
struct tcf_exts {int dummy; } ;
struct TYPE_2__ {void* classid; } ;
struct tc_u_knode {int /*<<< orphan*/  exts; int /*<<< orphan*/  indev; TYPE_1__ res; struct tc_u_hnode* ht_down; } ;
struct tc_u_hnode {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  tp_c; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t TCA_U32_CLASSID ; 
 size_t TCA_U32_INDEV ; 
 size_t TCA_U32_LINK ; 
 scalar_t__ TC_U32_KEY (void*) ; 
 void* nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  tcf_bind_filter (struct tcf_proto*,TYPE_1__*,unsigned long) ; 
 int tcf_change_indev (struct tcf_proto*,int /*<<< orphan*/ ,struct nlattr*) ; 
 int /*<<< orphan*/  tcf_exts_change (struct tcf_proto*,int /*<<< orphan*/ *,struct tcf_exts*) ; 
 int /*<<< orphan*/  tcf_exts_destroy (struct tcf_proto*,struct tcf_exts*) ; 
 int tcf_exts_validate (struct tcf_proto*,struct nlattr**,struct nlattr*,struct tcf_exts*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_tree_lock (struct tcf_proto*) ; 
 int /*<<< orphan*/  tcf_tree_unlock (struct tcf_proto*) ; 
 int /*<<< orphan*/  u32_ext_map ; 
 struct tc_u_hnode* u32_lookup_ht (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int u32_set_parms(struct tcf_proto *tp, unsigned long base,
			 struct tc_u_hnode *ht,
			 struct tc_u_knode *n, struct nlattr **tb,
			 struct nlattr *est)
{
	int err;
	struct tcf_exts e;

	err = tcf_exts_validate(tp, tb, est, &e, &u32_ext_map);
	if (err < 0)
		return err;

	err = -EINVAL;
	if (tb[TCA_U32_LINK]) {
		u32 handle = nla_get_u32(tb[TCA_U32_LINK]);
		struct tc_u_hnode *ht_down = NULL, *ht_old;

		if (TC_U32_KEY(handle))
			goto errout;

		if (handle) {
			ht_down = u32_lookup_ht(ht->tp_c, handle);

			if (ht_down == NULL)
				goto errout;
			ht_down->refcnt++;
		}

		tcf_tree_lock(tp);
		ht_old = n->ht_down;
		n->ht_down = ht_down;
		tcf_tree_unlock(tp);

		if (ht_old)
			ht_old->refcnt--;
	}
	if (tb[TCA_U32_CLASSID]) {
		n->res.classid = nla_get_u32(tb[TCA_U32_CLASSID]);
		tcf_bind_filter(tp, &n->res, base);
	}

#ifdef CONFIG_NET_CLS_IND
	if (tb[TCA_U32_INDEV]) {
		err = tcf_change_indev(tp, n->indev, tb[TCA_U32_INDEV]);
		if (err < 0)
			goto errout;
	}
#endif
	tcf_exts_change(tp, &n->exts, &e);

	return 0;
errout:
	tcf_exts_destroy(tp, &e);
	return err;
}