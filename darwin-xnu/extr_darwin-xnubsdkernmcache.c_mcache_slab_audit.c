#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int64_t ;
struct TYPE_4__ {intptr_t mc_chunksize; int /*<<< orphan*/  mc_align; int /*<<< orphan*/  mc_bufsize; } ;
typedef  TYPE_1__ mcache_t ;
struct TYPE_5__ {struct TYPE_5__* obj_next; } ;
typedef  TYPE_2__ mcache_obj_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int IS_P2ALIGNED (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCACHE_FREE_PATTERN ; 
 size_t P2ROUNDUP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  mcache_audit_free_verify_set (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mcache_set_pattern (int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static void
mcache_slab_audit(void *arg, mcache_obj_t *list, boolean_t alloc)
{
	mcache_t *cp = arg;
	size_t rsize = P2ROUNDUP(cp->mc_bufsize, sizeof (u_int64_t));
	void *base, **pbuf;

	while (list != NULL) {
		mcache_obj_t *next = list->obj_next;

		base = list;
		VERIFY(IS_P2ALIGNED(base, cp->mc_align));

		/* Get the original address */
		pbuf = (void **)((intptr_t)base - sizeof (void *));

		VERIFY(((intptr_t)base + rsize) <=
		    ((intptr_t)*pbuf + cp->mc_chunksize));

		if (!alloc)
			mcache_set_pattern(MCACHE_FREE_PATTERN, base, rsize);
		else
			mcache_audit_free_verify_set(NULL, base, 0, rsize);

		list = list->obj_next = next;
	}
}