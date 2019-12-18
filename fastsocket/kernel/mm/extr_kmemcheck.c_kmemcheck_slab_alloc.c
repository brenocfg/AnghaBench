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
struct kmem_cache {int flags; int /*<<< orphan*/  ctor; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int SLAB_NOTRACK ; 
 int __GFP_NOTRACK ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  kmemcheck_enabled ; 
 int /*<<< orphan*/  kmemcheck_mark_initialized (void*,size_t) ; 
 int /*<<< orphan*/  kmemcheck_mark_uninitialized (void*,size_t) ; 

void kmemcheck_slab_alloc(struct kmem_cache *s, gfp_t gfpflags, void *object,
			  size_t size)
{
	/*
	 * Has already been memset(), which initializes the shadow for us
	 * as well.
	 */
	if (gfpflags & __GFP_ZERO)
		return;

	/* No need to initialize the shadow of a non-tracked slab. */
	if (s->flags & SLAB_NOTRACK)
		return;

	if (!kmemcheck_enabled || gfpflags & __GFP_NOTRACK) {
		/*
		 * Allow notracked objects to be allocated from
		 * tracked caches. Note however that these objects
		 * will still get page faults on access, they just
		 * won't ever be flagged as uninitialized. If page
		 * faults are not acceptable, the slab cache itself
		 * should be marked NOTRACK.
		 */
		kmemcheck_mark_initialized(object, size);
	} else if (!s->ctor) {
		/*
		 * New objects should be marked uninitialized before
		 * they're returned to the called.
		 */
		kmemcheck_mark_uninitialized(object, size);
	}
}