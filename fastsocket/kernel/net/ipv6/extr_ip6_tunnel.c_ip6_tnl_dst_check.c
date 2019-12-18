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
struct ip6_tnl {struct dst_entry* dst_cache; int /*<<< orphan*/  dst_cookie; } ;
struct dst_entry {TYPE_1__* ops; scalar_t__ obsolete; } ;
struct TYPE_2__ {int /*<<< orphan*/ * (* check ) (struct dst_entry*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 int /*<<< orphan*/ * stub1 (struct dst_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct dst_entry *ip6_tnl_dst_check(struct ip6_tnl *t)
{
	struct dst_entry *dst = t->dst_cache;

	if (dst && dst->obsolete &&
	    dst->ops->check(dst, t->dst_cookie) == NULL) {
		t->dst_cache = NULL;
		dst_release(dst);
		return NULL;
	}

	return dst;
}