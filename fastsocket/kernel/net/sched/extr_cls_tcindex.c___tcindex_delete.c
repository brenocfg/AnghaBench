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
struct TYPE_2__ {int /*<<< orphan*/  class; } ;
struct tcindex_filter_result {int /*<<< orphan*/  exts; TYPE_1__ res; } ;
struct tcindex_filter {struct tcindex_filter* next; struct tcindex_filter_result result; } ;
struct tcindex_data {int hash; struct tcindex_filter** h; scalar_t__ perfect; } ;
struct tcf_proto {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct tcindex_data* PRIV (struct tcf_proto*) ; 
 int /*<<< orphan*/  kfree (struct tcindex_filter*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct tcf_proto*,unsigned long,struct tcindex_data*,struct tcindex_filter*) ; 
 int /*<<< orphan*/  tcf_exts_destroy (struct tcf_proto*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_tree_lock (struct tcf_proto*) ; 
 int /*<<< orphan*/  tcf_tree_unlock (struct tcf_proto*) ; 
 int /*<<< orphan*/  tcf_unbind_filter (struct tcf_proto*,TYPE_1__*) ; 

__attribute__((used)) static int
__tcindex_delete(struct tcf_proto *tp, unsigned long arg, int lock)
{
	struct tcindex_data *p = PRIV(tp);
	struct tcindex_filter_result *r = (struct tcindex_filter_result *) arg;
	struct tcindex_filter *f = NULL;

	pr_debug("tcindex_delete(tp %p,arg 0x%lx),p %p,f %p\n", tp, arg, p, f);
	if (p->perfect) {
		if (!r->res.class)
			return -ENOENT;
	} else {
		int i;
		struct tcindex_filter **walk = NULL;

		for (i = 0; i < p->hash; i++)
			for (walk = p->h+i; *walk; walk = &(*walk)->next)
				if (&(*walk)->result == r)
					goto found;
		return -ENOENT;

found:
		f = *walk;
		if (lock)
			tcf_tree_lock(tp);
		*walk = f->next;
		if (lock)
			tcf_tree_unlock(tp);
	}
	tcf_unbind_filter(tp, &r->res);
	tcf_exts_destroy(tp, &r->exts);
	kfree(f);
	return 0;
}