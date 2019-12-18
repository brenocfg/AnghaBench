#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* shared_region_pager_t ;
struct TYPE_4__ {int /*<<< orphan*/  mo_control; } ;
struct TYPE_5__ {int is_ready; scalar_t__ backing_object; TYPE_1__ sc_pgr_hdr; int /*<<< orphan*/  is_mapped; } ;

/* Variables and functions */
 scalar_t__ VM_OBJECT_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memory_object_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_deallocate (scalar_t__) ; 

void
shared_region_pager_terminate_internal(
	shared_region_pager_t pager)
{
	assert(pager->is_ready);
	assert(!pager->is_mapped);

	if (pager->backing_object != VM_OBJECT_NULL) {
		vm_object_deallocate(pager->backing_object);
		pager->backing_object = VM_OBJECT_NULL;
	}
	/* trigger the destruction of the memory object */
	memory_object_destroy(pager->sc_pgr_hdr.mo_control, 0);
}