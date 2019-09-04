#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* memory_object_control_t ;
struct TYPE_3__ {scalar_t__ moc_object; } ;

/* Variables and functions */
 scalar_t__ VM_OBJECT_NULL ; 
 int /*<<< orphan*/  assert (int) ; 

void
memory_object_control_disable(
	memory_object_control_t	control)
{
	assert(control->moc_object != VM_OBJECT_NULL);
	control->moc_object = VM_OBJECT_NULL;
}