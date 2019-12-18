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
typedef  int /*<<< orphan*/  vm_object_t ;
typedef  int /*<<< orphan*/  vm_object_offset_t ;
struct vm_shared_region_slide_info {int dummy; } ;
typedef  TYPE_1__* shared_region_pager_t ;
typedef  int /*<<< orphan*/  memory_object_t ;
struct TYPE_4__ {int /*<<< orphan*/  is_ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_SLEEP_DEFAULT ; 
 int /*<<< orphan*/  MEMORY_OBJECT_NULL ; 
 TYPE_1__* SHARED_REGION_PAGER_NULL ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_sleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* shared_region_pager_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_shared_region_slide_info*) ; 
 int /*<<< orphan*/  shared_region_pager_lock ; 

memory_object_t
shared_region_pager_setup(
	vm_object_t		backing_object,
	vm_object_offset_t	backing_offset,
	struct vm_shared_region_slide_info *slide_info)
{
	shared_region_pager_t	pager;

	/* create new pager */
	pager = shared_region_pager_create(
		backing_object,
		backing_offset,
		slide_info);
	if (pager == SHARED_REGION_PAGER_NULL) {
		/* could not create a new pager */
		return MEMORY_OBJECT_NULL;
	}

	lck_mtx_lock(&shared_region_pager_lock);
	while (!pager->is_ready) {
		lck_mtx_sleep(&shared_region_pager_lock,
			LCK_SLEEP_DEFAULT,
			&pager->is_ready,
			THREAD_UNINT);
	}
	lck_mtx_unlock(&shared_region_pager_lock);

	return (memory_object_t) pager;
}