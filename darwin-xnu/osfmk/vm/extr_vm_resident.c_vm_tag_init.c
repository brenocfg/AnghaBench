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
typedef  scalar_t__ vm_tag_t ;

/* Variables and functions */
 scalar_t__ VM_KERN_MEMORY_ANY ; 
 scalar_t__ VM_KERN_MEMORY_FIRST_DYNAMIC ; 
 scalar_t__ VM_MAX_TAG_VALUE ; 
 int /*<<< orphan*/  vm_tag_free_locked (scalar_t__) ; 

__attribute__((used)) static void
vm_tag_init(void)
{
    vm_tag_t tag;
    for (tag = VM_KERN_MEMORY_FIRST_DYNAMIC; tag < VM_KERN_MEMORY_ANY; tag++)
    {
        vm_tag_free_locked(tag);
    }

    for (tag = VM_KERN_MEMORY_ANY + 1; tag < VM_MAX_TAG_VALUE; tag++)
    {
        vm_tag_free_locked(tag);
    }
}