#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* allocation; size_t num_bytes; struct TYPE_7__* next; struct TYPE_7__* prev; } ;
typedef  TYPE_1__ AllocationEntry ;

/* Variables and functions */
 TYPE_1__* alloc_head ; 
 TYPE_1__* alloc_tail ; 
 TYPE_1__* find_allocation (void*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 void* realloc (void*,size_t) ; 
 int /*<<< orphan*/  tracking_free (void*) ; 
 void* tracking_malloc (size_t) ; 

void *
tracking_realloc(void *ptr, size_t size)
{
    AllocationEntry *entry;

    if (ptr == NULL) {
        /* By definition, this is equivalent to malloc(size) */
        return tracking_malloc(size);
    }
    if (size == 0) {
        /* By definition, this is equivalent to free(ptr) */
        tracking_free(ptr);
        return NULL;
    }

    /* Find the allocation entry for this memory */
    entry = find_allocation(ptr);
    if (entry == NULL) {
        printf("Attempting to realloc unallocated memory at %p\n", ptr);
        entry = malloc(sizeof(AllocationEntry));
        if (entry == NULL) {
            printf("Reallocator failure\n");
            return NULL;
        }
        entry->allocation = realloc(ptr, size);
        if (entry->allocation == NULL) {
            free(entry);
            return NULL;
        }

        /* Add to the list of allocations */
        entry->next = NULL;
        if (alloc_head == NULL) {
            entry->prev = NULL;
            alloc_head = alloc_tail = entry;
        } else {
            entry->prev = alloc_tail;
            alloc_tail->next = entry;
            alloc_tail = entry;
        }
    } else {
        entry->allocation = realloc(ptr, size);
        if (entry->allocation == NULL) {
            /* Realloc semantics say the original is still allocated */
            entry->allocation = ptr;
            return NULL;
        }
    }

    entry->num_bytes = size;
    return entry->allocation;
}