#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* atm_link_object_t ;
struct TYPE_4__ {int /*<<< orphan*/  descriptor; } ;

/* Variables and functions */
 int /*<<< orphan*/  atm_link_objects_zone ; 
 int /*<<< orphan*/  atm_task_descriptor_dealloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
atm_link_dealloc(atm_link_object_t link_object)
{
	/* Drop the reference on atm task descriptor. */
	atm_task_descriptor_dealloc(link_object->descriptor);
	zfree(atm_link_objects_zone, link_object);
}