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

/* Variables and functions */
 int /*<<< orphan*/  LCK_ATTR_NULL ; 
 int /*<<< orphan*/  LCK_GRP_ATTR_NULL ; 
 int /*<<< orphan*/  SHARED_REGION_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_shared_region_lck_grp ; 
 int /*<<< orphan*/  vm_shared_region_lock ; 
 int /*<<< orphan*/  vm_shared_region_queue ; 

void
vm_shared_region_init(void)
{
	SHARED_REGION_TRACE_DEBUG(
		("shared_region: -> init\n"));

	vm_shared_region_lck_grp = lck_grp_alloc_init("vm shared region",
						      LCK_GRP_ATTR_NULL);
	lck_mtx_init(&vm_shared_region_lock,
		     vm_shared_region_lck_grp,
		     LCK_ATTR_NULL);

	queue_init(&vm_shared_region_queue);

	SHARED_REGION_TRACE_DEBUG(
		("shared_region: <- init\n"));
}