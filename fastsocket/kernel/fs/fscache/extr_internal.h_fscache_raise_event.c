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
struct fscache_object {int /*<<< orphan*/  event_mask; int /*<<< orphan*/  events; int /*<<< orphan*/  debug_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int NR_FSCACHE_OBJECT_EVENTS ; 
 int /*<<< orphan*/  fscache_enqueue_object (struct fscache_object*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_and_set_bit (unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void fscache_raise_event(struct fscache_object *object,
				       unsigned event)
{
	BUG_ON(event >= NR_FSCACHE_OBJECT_EVENTS);
#if 0
	printk("*** fscache_raise_event(OBJ%d{%lx},%x)\n",
	       object->debug_id, object->event_mask, (1 << event));
#endif
	if (!test_and_set_bit(event, &object->events) &&
	    test_bit(event, &object->event_mask))
		fscache_enqueue_object(object);
}