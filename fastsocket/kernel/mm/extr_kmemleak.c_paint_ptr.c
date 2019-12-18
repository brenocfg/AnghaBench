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
 int KMEMLEAK_BLACK ; 
 int KMEMLEAK_GREY ; 
 struct kmemleak_object* find_and_get_object (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmemleak_warn (char*,unsigned long,char*) ; 
 int /*<<< orphan*/  paint_it (struct kmemleak_object*,int) ; 
 int /*<<< orphan*/  put_object (struct kmemleak_object*) ; 

__attribute__((used)) static void paint_ptr(unsigned long ptr, int color)
{
	struct kmemleak_object *object;

	object = find_and_get_object(ptr, 0);
	if (!object) {
		kmemleak_warn("Trying to color unknown object "
			      "at 0x%08lx as %s\n", ptr,
			      (color == KMEMLEAK_GREY) ? "Grey" :
			      (color == KMEMLEAK_BLACK) ? "Black" : "Unknown");
		return;
	}
	paint_it(object, color);
	put_object(object);
}