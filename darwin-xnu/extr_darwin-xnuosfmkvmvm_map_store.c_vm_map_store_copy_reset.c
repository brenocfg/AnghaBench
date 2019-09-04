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
typedef  int /*<<< orphan*/  vm_map_entry_t ;
typedef  TYPE_2__* vm_map_copy_t ;
struct TYPE_5__ {int nentries; } ;
struct TYPE_6__ {TYPE_1__ cpy_hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  vm_map_store_copy_reset_ll (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void
vm_map_store_copy_reset( vm_map_copy_t copy,vm_map_entry_t entry)
{
	int nentries = copy->cpy_hdr.nentries;
	vm_map_store_copy_reset_ll(copy, entry, nentries);
#ifdef VM_MAP_STORE_USE_RB
	if (vm_map_store_has_RB_support( &copy->c_u.hdr )) {
		vm_map_store_copy_reset_rb(copy, entry, nentries);
	}
#endif
}