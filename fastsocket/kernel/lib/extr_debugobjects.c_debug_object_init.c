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
struct debug_obj_descr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __debug_object_init (void*,struct debug_obj_descr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_objects_enabled ; 

void debug_object_init(void *addr, struct debug_obj_descr *descr)
{
	if (!debug_objects_enabled)
		return;

	__debug_object_init(addr, descr, 0);
}