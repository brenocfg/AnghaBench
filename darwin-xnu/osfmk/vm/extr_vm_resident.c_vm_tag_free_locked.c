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
typedef  int vm_tag_t ;
typedef  int uint64_t ;
typedef  size_t uint32_t ;

/* Variables and functions */
 int VM_KERN_MEMORY_ANY ; 
 int /*<<< orphan*/  assert (int) ; 
 int* free_tag_bits ; 

__attribute__((used)) static void
vm_tag_free_locked(vm_tag_t tag)
{
    uint64_t avail;
    uint32_t idx;
    uint64_t bit;

    if (VM_KERN_MEMORY_ANY == tag) return;

    idx = (tag >> 6);
    avail = free_tag_bits[idx];
    tag &= 63;
    bit = (1ULL << (63 - tag));
    assert(!(avail & bit));
    free_tag_bits[idx] = (avail | bit);
}