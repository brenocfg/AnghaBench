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
struct tcindex_data {struct tcindex_data* h; struct tcindex_data* perfect; } ;
struct tcf_walker {int /*<<< orphan*/ * fn; scalar_t__ skip; scalar_t__ count; } ;
struct tcf_proto {int /*<<< orphan*/ * root; } ;

/* Variables and functions */
 struct tcindex_data* PRIV (struct tcf_proto*) ; 
 int /*<<< orphan*/  kfree (struct tcindex_data*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct tcf_proto*,struct tcindex_data*) ; 
 int /*<<< orphan*/  tcindex_destroy_element ; 
 int /*<<< orphan*/  tcindex_walk (struct tcf_proto*,struct tcf_walker*) ; 

__attribute__((used)) static void tcindex_destroy(struct tcf_proto *tp)
{
	struct tcindex_data *p = PRIV(tp);
	struct tcf_walker walker;

	pr_debug("tcindex_destroy(tp %p),p %p\n", tp, p);
	walker.count = 0;
	walker.skip = 0;
	walker.fn = &tcindex_destroy_element;
	tcindex_walk(tp, &walker);
	kfree(p->perfect);
	kfree(p->h);
	kfree(p);
	tp->root = NULL;
}