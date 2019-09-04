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
typedef  TYPE_1__* shared_region_pager_t ;
typedef  TYPE_2__* memory_object_t ;
struct TYPE_6__ {int /*<<< orphan*/ * mo_pager_ops; } ;
struct TYPE_5__ {scalar_t__ ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  shared_region_pager_ops ; 

shared_region_pager_t
shared_region_pager_lookup(
	memory_object_t	 mem_obj)
{
	shared_region_pager_t	pager;

	assert(mem_obj->mo_pager_ops == &shared_region_pager_ops);
	pager = (shared_region_pager_t)(uintptr_t) mem_obj;
	assert(pager->ref_count > 0);
	return pager;
}