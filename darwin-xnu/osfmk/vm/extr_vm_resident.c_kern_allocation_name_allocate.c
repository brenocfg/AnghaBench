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
typedef  int uint32_t ;
typedef  TYPE_1__* kern_allocation_name_t ;
struct TYPE_6__ {int refcount; int subtotalscount; int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KA_NAME (TYPE_1__*) ; 
 int /*<<< orphan*/  KA_SIZE (int,int) ; 
 scalar_t__ MACH_MEMORY_INFO_NAME_MAX_LEN ; 
 int VM_TAG_NAME_LEN_SHIFT ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* kalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ strnlen (char const*,scalar_t__) ; 

kern_allocation_name_t
kern_allocation_name_allocate(const char * name, uint32_t subtotalscount)
{
    uint32_t namelen;

    namelen = (uint32_t) strnlen(name, MACH_MEMORY_INFO_NAME_MAX_LEN - 1);

    kern_allocation_name_t allocation;
    allocation = kalloc(KA_SIZE(namelen, subtotalscount));
    bzero(allocation, KA_SIZE(namelen, subtotalscount));

    allocation->refcount       = 1;
    allocation->subtotalscount = subtotalscount;
    allocation->flags          = (namelen << VM_TAG_NAME_LEN_SHIFT);
    strlcpy(KA_NAME(allocation), name, namelen + 1);

    return (allocation);
}