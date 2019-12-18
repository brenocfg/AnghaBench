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
struct tcf_proto {int /*<<< orphan*/  q; scalar_t__ root; } ;
struct route4_head {int /*<<< orphan*/ ** table; } ;
struct route4_filter {unsigned int handle; int /*<<< orphan*/  id; struct route4_filter* next; struct route4_bucket* bkt; } ;
struct route4_bucket {struct route4_filter** ht; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t from_hash (unsigned int) ; 
 int /*<<< orphan*/  kfree (struct route4_bucket*) ; 
 int /*<<< orphan*/  route4_delete_filter (struct tcf_proto*,struct route4_filter*) ; 
 int /*<<< orphan*/  route4_reset_fastmap (int /*<<< orphan*/ ,struct route4_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_tree_lock (struct tcf_proto*) ; 
 int /*<<< orphan*/  tcf_tree_unlock (struct tcf_proto*) ; 
 size_t to_hash (unsigned int) ; 

__attribute__((used)) static int route4_delete(struct tcf_proto *tp, unsigned long arg)
{
	struct route4_head *head = (struct route4_head*)tp->root;
	struct route4_filter **fp, *f = (struct route4_filter*)arg;
	unsigned h = 0;
	struct route4_bucket *b;
	int i;

	if (!head || !f)
		return -EINVAL;

	h = f->handle;
	b = f->bkt;

	for (fp = &b->ht[from_hash(h>>16)]; *fp; fp = &(*fp)->next) {
		if (*fp == f) {
			tcf_tree_lock(tp);
			*fp = f->next;
			tcf_tree_unlock(tp);

			route4_reset_fastmap(tp->q, head, f->id);
			route4_delete_filter(tp, f);

			/* Strip tree */

			for (i=0; i<=32; i++)
				if (b->ht[i])
					return 0;

			/* OK, session has no flows */
			tcf_tree_lock(tp);
			head->table[to_hash(h)] = NULL;
			tcf_tree_unlock(tp);

			kfree(b);
			return 0;
		}
	}
	return 0;
}