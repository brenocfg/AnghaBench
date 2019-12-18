#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* allocation; struct TYPE_4__* next; } ;
typedef  TYPE_1__ AllocationEntry ;

/* Variables and functions */
 TYPE_1__* alloc_head ; 

__attribute__((used)) static AllocationEntry *
find_allocation(void *ptr)
{
    AllocationEntry *entry;

    for (entry = alloc_head; entry != NULL; entry = entry->next) {
        if (entry->allocation == ptr) {
            return entry;
        }
    }
    return NULL;
}