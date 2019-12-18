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
typedef  enum debug_obj_state { ____Placeholder_debug_obj_state } debug_obj_state ;

/* Variables and functions */
 int /*<<< orphan*/  debug_objects_fixups ; 

__attribute__((used)) static void
debug_object_fixup(int (*fixup)(void *addr, enum debug_obj_state state),
		   void * addr, enum debug_obj_state state)
{
	if (fixup)
		debug_objects_fixups += fixup(addr, state);
}