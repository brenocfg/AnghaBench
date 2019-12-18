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
typedef  scalar_t__ u32 ;
struct tcindex_filter_result {int dummy; } ;
struct tcindex_data {scalar_t__ alloc_hash; scalar_t__ perfect; } ;
struct tcf_proto {int dummy; } ;

/* Variables and functions */
 struct tcindex_data* PRIV (struct tcf_proto*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct tcf_proto*,scalar_t__) ; 
 scalar_t__ tcindex_filter_is_set (struct tcindex_filter_result*) ; 
 struct tcindex_filter_result* tcindex_lookup (struct tcindex_data*,scalar_t__) ; 

__attribute__((used)) static unsigned long tcindex_get(struct tcf_proto *tp, u32 handle)
{
	struct tcindex_data *p = PRIV(tp);
	struct tcindex_filter_result *r;

	pr_debug("tcindex_get(tp %p,handle 0x%08x)\n", tp, handle);
	if (p->perfect && handle >= p->alloc_hash)
		return 0;
	r = tcindex_lookup(p, handle);
	return r && tcindex_filter_is_set(r) ? (unsigned long) r : 0UL;
}