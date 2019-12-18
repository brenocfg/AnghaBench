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
typedef  scalar_t__ u32 ;
struct ip_vs_dest {scalar_t__ dst_rtos; struct dst_entry* dst_cache; int /*<<< orphan*/  dst_cookie; } ;
struct dst_entry {TYPE_1__* ops; scalar_t__ obsolete; } ;
struct TYPE_2__ {int /*<<< orphan*/ * (* check ) (struct dst_entry*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dst_hold (struct dst_entry*) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 int /*<<< orphan*/ * stub1 (struct dst_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct dst_entry *
__ip_vs_dst_check(struct ip_vs_dest *dest, u32 rtos)
{
	struct dst_entry *dst = dest->dst_cache;

	if (!dst)
		return NULL;
	if ((dst->obsolete || rtos != dest->dst_rtos) &&
	    dst->ops->check(dst, dest->dst_cookie) == NULL) {
		dest->dst_cache = NULL;
		dst_release(dst);
		return NULL;
	}
	dst_hold(dst);
	return dst;
}