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
typedef  int u_int32_t ;
struct TYPE_4__ {intptr_t mc_bufsize; int mc_flags; int mc_align; intptr_t mc_chunksize; int /*<<< orphan*/  mc_slab_zone; } ;
typedef  TYPE_1__ mcache_t ;
struct TYPE_5__ {struct TYPE_5__* obj_next; } ;
typedef  TYPE_2__ mcache_obj_t ;

/* Variables and functions */
 int IS_P2ALIGNED (void*,int) ; 
 int /*<<< orphan*/  MCACHE_FREE_PATTERN ; 
 int MCF_DEBUG ; 
 size_t P2ROUNDUP (intptr_t,int) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  mcache_set_pattern (int /*<<< orphan*/ ,void*,size_t) ; 
 void* zalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
mcache_slab_alloc(void *arg, mcache_obj_t ***plist, unsigned int num,
    int wait)
{
#pragma unused(wait)
	mcache_t *cp = arg;
	unsigned int need = num;
	size_t rsize = P2ROUNDUP(cp->mc_bufsize, sizeof (u_int64_t));
	u_int32_t flags = cp->mc_flags;
	void *buf, *base, **pbuf;
	mcache_obj_t **list = *plist;

	*list = NULL;

	for (;;) {
		buf = zalloc(cp->mc_slab_zone);
		if (buf == NULL)
			break;

		/* Get the aligned base address for this object */
		base = (void *)P2ROUNDUP((intptr_t)buf + sizeof (u_int64_t),
		    cp->mc_align);

		/*
		 * Wind back a pointer size from the aligned base and
		 * save the original address so we can free it later.
		 */
		pbuf = (void **)((intptr_t)base - sizeof (void *));
		*pbuf = buf;

		VERIFY (((intptr_t)base + cp->mc_bufsize) <=
		    ((intptr_t)buf + cp->mc_chunksize));

		/*
		 * If auditing is enabled, patternize the contents of
		 * the buffer starting from the 64-bit aligned base to
		 * the end of the buffer; the length is rounded up to
		 * the nearest 64-bit multiply; this is because we use
		 * 64-bit memory access to set/check the pattern.
		 */
		if (flags & MCF_DEBUG) {
			VERIFY(((intptr_t)base + rsize) <=
			    ((intptr_t)buf + cp->mc_chunksize));
			mcache_set_pattern(MCACHE_FREE_PATTERN, base, rsize);
		}

		VERIFY(IS_P2ALIGNED(base, cp->mc_align));
		*list = (mcache_obj_t *)base;

		(*list)->obj_next = NULL;
		list = *plist = &(*list)->obj_next;

		/* If we got them all, return to mcache */
		if (--need == 0)
			break;
	}

	return (num - need);
}