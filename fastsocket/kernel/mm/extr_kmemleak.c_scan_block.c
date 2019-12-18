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
struct kmemleak_object {int /*<<< orphan*/  lock; int /*<<< orphan*/  gray_list; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 void* BYTES_PER_POINTER ; 
 unsigned long* PTR_ALIGN (void*,void*) ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 scalar_t__ color_gray (struct kmemleak_object*) ; 
 int /*<<< orphan*/  color_white (struct kmemleak_object*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 struct kmemleak_object* find_and_get_object (unsigned long,int) ; 
 int /*<<< orphan*/  gray_list ; 
 int /*<<< orphan*/  kmemcheck_is_obj_initialized (unsigned long,void*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_object (struct kmemleak_object*) ; 
 scalar_t__ scan_should_stop () ; 
 int /*<<< orphan*/  spin_lock_irqsave_nested (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void scan_block(void *_start, void *_end,
		       struct kmemleak_object *scanned, int allow_resched)
{
	unsigned long *ptr;
	unsigned long *start = PTR_ALIGN(_start, BYTES_PER_POINTER);
	unsigned long *end = _end - (BYTES_PER_POINTER - 1);

	for (ptr = start; ptr < end; ptr++) {
		struct kmemleak_object *object;
		unsigned long flags;
		unsigned long pointer;

		if (allow_resched)
			cond_resched();
		if (scan_should_stop())
			break;

		/* don't scan uninitialized memory */
		if (!kmemcheck_is_obj_initialized((unsigned long)ptr,
						  BYTES_PER_POINTER))
			continue;

		pointer = *ptr;

		object = find_and_get_object(pointer, 1);
		if (!object)
			continue;
		if (object == scanned) {
			/* self referenced, ignore */
			put_object(object);
			continue;
		}

		/*
		 * Avoid the lockdep recursive warning on object->lock being
		 * previously acquired in scan_object(). These locks are
		 * enclosed by scan_mutex.
		 */
		spin_lock_irqsave_nested(&object->lock, flags,
					 SINGLE_DEPTH_NESTING);
		if (!color_white(object)) {
			/* non-orphan, ignored or new */
			spin_unlock_irqrestore(&object->lock, flags);
			put_object(object);
			continue;
		}

		/*
		 * Increase the object's reference count (number of pointers
		 * to the memory block). If this count reaches the required
		 * minimum, the object's color will become gray and it will be
		 * added to the gray_list.
		 */
		object->count++;
		if (color_gray(object))
			list_add_tail(&object->gray_list, &gray_list);
		else
			put_object(object);
		spin_unlock_irqrestore(&object->lock, flags);
	}
}