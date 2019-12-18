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
typedef  int u32 ;
struct tcf_proto {int /*<<< orphan*/  q; struct route4_head* root; } ;
struct route4_head {struct route4_bucket** table; } ;
struct route4_filter {int handle; int /*<<< orphan*/  id; struct route4_filter* next; TYPE_1__* bkt; } ;
struct route4_bucket {struct route4_filter** ht; } ;
struct nlattr {int dummy; } ;
struct TYPE_2__ {struct route4_filter** ht; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t TCA_OPTIONS ; 
 size_t TCA_RATE ; 
 int /*<<< orphan*/  TCA_ROUTE4_MAX ; 
 unsigned int from_hash (int) ; 
 int /*<<< orphan*/  kfree (struct route4_filter*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  route4_policy ; 
 int /*<<< orphan*/  route4_reset_fastmap (int /*<<< orphan*/ ,struct route4_head*,int /*<<< orphan*/ ) ; 
 int route4_set_parms (struct tcf_proto*,unsigned long,struct route4_filter*,int,struct route4_head*,struct nlattr**,struct nlattr*,int) ; 
 int /*<<< orphan*/  tcf_tree_lock (struct tcf_proto*) ; 
 int /*<<< orphan*/  tcf_tree_unlock (struct tcf_proto*) ; 
 unsigned int to_hash (int) ; 

__attribute__((used)) static int route4_change(struct tcf_proto *tp, unsigned long base,
		       u32 handle,
		       struct nlattr **tca,
		       unsigned long *arg)
{
	struct route4_head *head = tp->root;
	struct route4_filter *f, *f1, **fp;
	struct route4_bucket *b;
	struct nlattr *opt = tca[TCA_OPTIONS];
	struct nlattr *tb[TCA_ROUTE4_MAX + 1];
	unsigned int h, th;
	u32 old_handle = 0;
	int err;

	if (opt == NULL)
		return handle ? -EINVAL : 0;

	err = nla_parse_nested(tb, TCA_ROUTE4_MAX, opt, route4_policy);
	if (err < 0)
		return err;

	if ((f = (struct route4_filter*)*arg) != NULL) {
		if (f->handle != handle && handle)
			return -EINVAL;

		if (f->bkt)
			old_handle = f->handle;

		err = route4_set_parms(tp, base, f, handle, head, tb,
			tca[TCA_RATE], 0);
		if (err < 0)
			return err;

		goto reinsert;
	}

	err = -ENOBUFS;
	if (head == NULL) {
		head = kzalloc(sizeof(struct route4_head), GFP_KERNEL);
		if (head == NULL)
			goto errout;

		tcf_tree_lock(tp);
		tp->root = head;
		tcf_tree_unlock(tp);
	}

	f = kzalloc(sizeof(struct route4_filter), GFP_KERNEL);
	if (f == NULL)
		goto errout;

	err = route4_set_parms(tp, base, f, handle, head, tb,
		tca[TCA_RATE], 1);
	if (err < 0)
		goto errout;

reinsert:
	h = from_hash(f->handle >> 16);
	for (fp = &f->bkt->ht[h]; (f1=*fp) != NULL; fp = &f1->next)
		if (f->handle < f1->handle)
			break;

	f->next = f1;
	tcf_tree_lock(tp);
	*fp = f;

	if (old_handle && f->handle != old_handle) {
		th = to_hash(old_handle);
		h = from_hash(old_handle >> 16);
		if ((b = head->table[th]) != NULL) {
			for (fp = &b->ht[h]; *fp; fp = &(*fp)->next) {
				if (*fp == f) {
					*fp = f->next;
					break;
				}
			}
		}
	}
	tcf_tree_unlock(tp);

	route4_reset_fastmap(tp->q, head, f->id);
	*arg = (unsigned long)f;
	return 0;

errout:
	kfree(f);
	return err;
}