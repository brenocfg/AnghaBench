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
struct slab {int dummy; } ;
struct kmem_cache {int num; int flags; int buffer_size; int /*<<< orphan*/  (* ctor ) (void*) ;} ;

/* Variables and functions */
 int BUFCTL_END ; 
 scalar_t__ OFF_SLAB (struct kmem_cache*) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  POISON_FREE ; 
 scalar_t__ RED_INACTIVE ; 
 int SLAB_POISON ; 
 int SLAB_RED_ZONE ; 
 int SLAB_STORE_USER ; 
 scalar_t__* dbg_redzone1 (struct kmem_cache*,void*) ; 
 scalar_t__* dbg_redzone2 (struct kmem_cache*,void*) ; 
 int /*<<< orphan*/ ** dbg_userword (struct kmem_cache*,void*) ; 
 void* index_to_obj (struct kmem_cache*,struct slab*,int) ; 
 int /*<<< orphan*/  kernel_map_pages (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int obj_offset (struct kmem_cache*) ; 
 int /*<<< orphan*/  poison_obj (struct kmem_cache*,void*,int /*<<< orphan*/ ) ; 
 int* slab_bufctl (struct slab*) ; 
 int /*<<< orphan*/  slab_error (struct kmem_cache*,char*) ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 int /*<<< orphan*/  stub2 (void*) ; 
 int /*<<< orphan*/  virt_to_page (void*) ; 

__attribute__((used)) static void cache_init_objs(struct kmem_cache *cachep,
			    struct slab *slabp)
{
	int i;

	for (i = 0; i < cachep->num; i++) {
		void *objp = index_to_obj(cachep, slabp, i);
#if DEBUG
		/* need to poison the objs? */
		if (cachep->flags & SLAB_POISON)
			poison_obj(cachep, objp, POISON_FREE);
		if (cachep->flags & SLAB_STORE_USER)
			*dbg_userword(cachep, objp) = NULL;

		if (cachep->flags & SLAB_RED_ZONE) {
			*dbg_redzone1(cachep, objp) = RED_INACTIVE;
			*dbg_redzone2(cachep, objp) = RED_INACTIVE;
		}
		/*
		 * Constructors are not allowed to allocate memory from the same
		 * cache which they are a constructor for.  Otherwise, deadlock.
		 * They must also be threaded.
		 */
		if (cachep->ctor && !(cachep->flags & SLAB_POISON))
			cachep->ctor(objp + obj_offset(cachep));

		if (cachep->flags & SLAB_RED_ZONE) {
			if (*dbg_redzone2(cachep, objp) != RED_INACTIVE)
				slab_error(cachep, "constructor overwrote the"
					   " end of an object");
			if (*dbg_redzone1(cachep, objp) != RED_INACTIVE)
				slab_error(cachep, "constructor overwrote the"
					   " start of an object");
		}
		if ((cachep->buffer_size % PAGE_SIZE) == 0 &&
			    OFF_SLAB(cachep) && cachep->flags & SLAB_POISON)
			kernel_map_pages(virt_to_page(objp),
					 cachep->buffer_size / PAGE_SIZE, 0);
#else
		if (cachep->ctor)
			cachep->ctor(objp);
#endif
		slab_bufctl(slabp)[i] = i + 1;
	}
	slab_bufctl(slabp)[i - 1] = BUFCTL_END;
}