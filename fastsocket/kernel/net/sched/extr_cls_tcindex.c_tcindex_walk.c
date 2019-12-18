#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tcindex_filter {int /*<<< orphan*/  result; struct tcindex_filter* next; } ;
struct tcindex_data {int hash; struct tcindex_filter** h; TYPE_2__* perfect; } ;
struct tcf_walker {scalar_t__ count; scalar_t__ skip; scalar_t__ (* fn ) (struct tcf_proto*,unsigned long,struct tcf_walker*) ;int stop; } ;
struct tcf_proto {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  class; } ;
struct TYPE_4__ {TYPE_1__ res; } ;

/* Variables and functions */
 struct tcindex_data* PRIV (struct tcf_proto*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct tcf_proto*,struct tcf_walker*,struct tcindex_data*) ; 
 scalar_t__ stub1 (struct tcf_proto*,unsigned long,struct tcf_walker*) ; 
 scalar_t__ stub2 (struct tcf_proto*,unsigned long,struct tcf_walker*) ; 

__attribute__((used)) static void tcindex_walk(struct tcf_proto *tp, struct tcf_walker *walker)
{
	struct tcindex_data *p = PRIV(tp);
	struct tcindex_filter *f, *next;
	int i;

	pr_debug("tcindex_walk(tp %p,walker %p),p %p\n", tp, walker, p);
	if (p->perfect) {
		for (i = 0; i < p->hash; i++) {
			if (!p->perfect[i].res.class)
				continue;
			if (walker->count >= walker->skip) {
				if (walker->fn(tp,
				    (unsigned long) (p->perfect+i), walker)
				     < 0) {
					walker->stop = 1;
					return;
				}
			}
			walker->count++;
		}
	}
	if (!p->h)
		return;
	for (i = 0; i < p->hash; i++) {
		for (f = p->h[i]; f; f = next) {
			next = f->next;
			if (walker->count >= walker->skip) {
				if (walker->fn(tp, (unsigned long) &f->result,
				    walker) < 0) {
					walker->stop = 1;
					return;
				}
			}
			walker->count++;
		}
	}
}