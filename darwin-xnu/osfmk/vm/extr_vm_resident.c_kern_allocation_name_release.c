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
typedef  TYPE_1__* kern_allocation_name_t ;
struct TYPE_5__ {scalar_t__ refcount; int /*<<< orphan*/  subtotalscount; } ;

/* Variables and functions */
 int /*<<< orphan*/  KA_NAME_LEN (TYPE_1__*) ; 
 int /*<<< orphan*/  KA_SIZE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OSAddAtomic16 (int,scalar_t__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
kern_allocation_name_release(kern_allocation_name_t allocation)
{
    assert(allocation->refcount > 0);
    if (1 == OSAddAtomic16(-1, &allocation->refcount))
    {
        kfree(allocation, KA_SIZE(KA_NAME_LEN(allocation), allocation->subtotalscount));
    }
}