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
typedef  int /*<<< orphan*/  memory_object_control_t ;

/* Variables and functions */
 int /*<<< orphan*/  mem_obj_control_zone ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
memory_object_control_deallocate(
	memory_object_control_t	control)
{
	zfree(mem_obj_control_zone, control);
}