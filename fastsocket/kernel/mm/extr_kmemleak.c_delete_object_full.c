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
struct kmemleak_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __delete_object (struct kmemleak_object*) ; 
 struct kmemleak_object* find_and_get_object (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmemleak_warn (char*,unsigned long) ; 
 int /*<<< orphan*/  put_object (struct kmemleak_object*) ; 

__attribute__((used)) static void delete_object_full(unsigned long ptr)
{
	struct kmemleak_object *object;

	object = find_and_get_object(ptr, 0);
	if (!object) {
#ifdef DEBUG
		kmemleak_warn("Freeing unknown object at 0x%08lx\n",
			      ptr);
#endif
		return;
	}
	__delete_object(object);
	put_object(object);
}