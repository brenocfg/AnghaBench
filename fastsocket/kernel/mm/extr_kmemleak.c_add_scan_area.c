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
struct kmemleak_scan_area {unsigned long offset; size_t length; int /*<<< orphan*/  node; } ;
struct kmemleak_object {unsigned long size; int /*<<< orphan*/  lock; int /*<<< orphan*/  area_list; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int GFP_KMEMLEAK_MASK ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_object_info (struct kmemleak_object*) ; 
 struct kmemleak_object* find_and_get_object (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct kmemleak_scan_area* kmem_cache_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct kmemleak_scan_area*) ; 
 int /*<<< orphan*/  kmemleak_warn (char*,...) ; 
 int /*<<< orphan*/  put_object (struct kmemleak_object*) ; 
 int /*<<< orphan*/  scan_area_cache ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void add_scan_area(unsigned long ptr, unsigned long offset,
			  size_t length, gfp_t gfp)
{
	unsigned long flags;
	struct kmemleak_object *object;
	struct kmemleak_scan_area *area;

	object = find_and_get_object(ptr, 0);
	if (!object) {
		kmemleak_warn("Adding scan area to unknown object at 0x%08lx\n",
			      ptr);
		return;
	}

	area = kmem_cache_alloc(scan_area_cache, gfp & GFP_KMEMLEAK_MASK);
	if (!area) {
		kmemleak_warn("Cannot allocate a scan area\n");
		goto out;
	}

	spin_lock_irqsave(&object->lock, flags);
	if (offset + length > object->size) {
		kmemleak_warn("Scan area larger than object 0x%08lx\n", ptr);
		dump_object_info(object);
		kmem_cache_free(scan_area_cache, area);
		goto out_unlock;
	}

	INIT_HLIST_NODE(&area->node);
	area->offset = offset;
	area->length = length;

	hlist_add_head(&area->node, &object->area_list);
out_unlock:
	spin_unlock_irqrestore(&object->lock, flags);
out:
	put_object(object);
}