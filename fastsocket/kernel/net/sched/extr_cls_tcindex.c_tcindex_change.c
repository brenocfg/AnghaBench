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
struct tcindex_filter_result {int dummy; } ;
struct tcindex_data {int dummy; } ;
struct tcf_proto {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 struct tcindex_data* PRIV (struct tcf_proto*) ; 
 size_t TCA_OPTIONS ; 
 size_t TCA_RATE ; 
 int /*<<< orphan*/  TCA_TCINDEX_MAX ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct tcf_proto*,int /*<<< orphan*/ ,struct nlattr**,unsigned long*,struct nlattr*,struct tcindex_data*,struct tcindex_filter_result*,unsigned long) ; 
 int /*<<< orphan*/  tcindex_policy ; 
 int tcindex_set_parms (struct tcf_proto*,unsigned long,int /*<<< orphan*/ ,struct tcindex_data*,struct tcindex_filter_result*,struct nlattr**,struct nlattr*) ; 

__attribute__((used)) static int
tcindex_change(struct tcf_proto *tp, unsigned long base, u32 handle,
	       struct nlattr **tca, unsigned long *arg)
{
	struct nlattr *opt = tca[TCA_OPTIONS];
	struct nlattr *tb[TCA_TCINDEX_MAX + 1];
	struct tcindex_data *p = PRIV(tp);
	struct tcindex_filter_result *r = (struct tcindex_filter_result *) *arg;
	int err;

	pr_debug("tcindex_change(tp %p,handle 0x%08x,tca %p,arg %p),opt %p,"
	    "p %p,r %p,*arg 0x%lx\n",
	    tp, handle, tca, arg, opt, p, r, arg ? *arg : 0L);

	if (!opt)
		return 0;

	err = nla_parse_nested(tb, TCA_TCINDEX_MAX, opt, tcindex_policy);
	if (err < 0)
		return err;

	return tcindex_set_parms(tp, base, handle, p, r, tb, tca[TCA_RATE]);
}