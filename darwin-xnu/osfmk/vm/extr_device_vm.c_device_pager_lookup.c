#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* memory_object_t ;
typedef  TYPE_2__* device_pager_t ;
struct TYPE_6__ {scalar_t__ ref_count; } ;
struct TYPE_5__ {int /*<<< orphan*/ * mo_pager_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  device_pager_ops ; 

device_pager_t
device_pager_lookup(
	memory_object_t	mem_obj)
{
	device_pager_t	device_object;

	assert(mem_obj->mo_pager_ops == &device_pager_ops);
	device_object = (device_pager_t)mem_obj;
	assert(device_object->ref_count > 0);
	return device_object;
}