#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  allocation; scalar_t__ num_bytes; struct TYPE_3__* next; } ;
typedef  TYPE_1__ AllocationEntry ;

/* Variables and functions */
 TYPE_1__* alloc_head ; 
 int /*<<< orphan*/  printf (char*,unsigned long,int /*<<< orphan*/ ) ; 

int
tracking_report(void)
{
    AllocationEntry *entry;

    if (alloc_head == NULL)
        return 1;

    /* Otherwise we have allocations that haven't been freed */
    for (entry = alloc_head; entry != NULL; entry = entry->next)
    {
        printf("Allocated %lu bytes at %p\n",
                (long unsigned)entry->num_bytes, entry->allocation);
    }
    return 0;
}