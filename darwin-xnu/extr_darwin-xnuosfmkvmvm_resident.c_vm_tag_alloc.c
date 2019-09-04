#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_tag_t ;
struct TYPE_6__ {int flags; scalar_t__ tag; } ;
typedef  TYPE_1__ vm_allocation_site_t ;

/* Variables and functions */
 scalar_t__ VM_KERN_MEMORY_NONE ; 
 int VM_TAG_BT ; 
 int /*<<< orphan*/  kern_allocation_name_release (TYPE_1__*) ; 
 int /*<<< orphan*/  lck_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_allocation_sites_lock ; 
 int /*<<< orphan*/  vm_tag_alloc_locked (TYPE_1__*,TYPE_1__**) ; 
 scalar_t__ vm_tag_bt () ; 

vm_tag_t
vm_tag_alloc(vm_allocation_site_t * site)
{
    vm_tag_t tag;
    vm_allocation_site_t * releasesite;

    if (VM_TAG_BT & site->flags)
    {
		tag = vm_tag_bt();
		if (VM_KERN_MEMORY_NONE != tag) return (tag);
    }

    if (!site->tag) 
    {
		releasesite = NULL;
		lck_spin_lock(&vm_allocation_sites_lock);
		vm_tag_alloc_locked(site, &releasesite);
		lck_spin_unlock(&vm_allocation_sites_lock);
        if (releasesite) kern_allocation_name_release(releasesite);
    }

    return (site->tag);
}