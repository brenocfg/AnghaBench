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
struct kmemleak_object {unsigned long pointer; unsigned long size; int /*<<< orphan*/  min_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __delete_object (struct kmemleak_object*) ; 
 int /*<<< orphan*/  create_object (unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct kmemleak_object* find_and_get_object (unsigned long,int) ; 
 int /*<<< orphan*/  kmemleak_warn (char*,unsigned long,size_t) ; 
 int /*<<< orphan*/  put_object (struct kmemleak_object*) ; 

__attribute__((used)) static void delete_object_part(unsigned long ptr, size_t size)
{
	struct kmemleak_object *object;
	unsigned long start, end;

	object = find_and_get_object(ptr, 1);
	if (!object) {
#ifdef DEBUG
		kmemleak_warn("Partially freeing unknown object at 0x%08lx "
			      "(size %zu)\n", ptr, size);
#endif
		return;
	}
	__delete_object(object);

	/*
	 * Create one or two objects that may result from the memory block
	 * split. Note that partial freeing is only done by free_bootmem() and
	 * this happens before kmemleak_init() is called. The path below is
	 * only executed during early log recording in kmemleak_init(), so
	 * GFP_KERNEL is enough.
	 */
	start = object->pointer;
	end = object->pointer + object->size;
	if (ptr > start)
		create_object(start, ptr - start, object->min_count,
			      GFP_KERNEL);
	if (ptr + size < end)
		create_object(ptr + size, end - ptr - size, object->min_count,
			      GFP_KERNEL);

	put_object(object);
}