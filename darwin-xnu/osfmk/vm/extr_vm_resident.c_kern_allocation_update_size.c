#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  TYPE_1__* kern_allocation_name_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {scalar_t__ total; scalar_t__ peak; int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 scalar_t__ OSAddAtomic64 (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  OSCompareAndSwap64 (scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  assertf (int,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  vm_tag_alloc (TYPE_1__*) ; 

void
kern_allocation_update_size(kern_allocation_name_t allocation, int64_t delta)
{
    uint64_t prior;

    if (delta < 0) {
		assertf(allocation->total >= ((uint64_t)-delta), "name %p", allocation);
    }
    prior = OSAddAtomic64(delta, &allocation->total);

#if DEBUG || DEVELOPMENT

    uint64_t new, peak;
	new = prior + delta;
    do
    {
        peak = allocation->peak;
        if (new <= peak) break;
    }
    while (!OSCompareAndSwap64(peak, new, &allocation->peak));

#endif /* DEBUG || DEVELOPMENT */

    if (!prior && !allocation->tag) vm_tag_alloc(allocation);
}