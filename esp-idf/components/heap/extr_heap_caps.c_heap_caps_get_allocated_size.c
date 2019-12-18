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
struct TYPE_3__ {int /*<<< orphan*/  heap; } ;
typedef  TYPE_1__ heap_t ;

/* Variables and functions */
 TYPE_1__* find_containing_heap (void*) ; 
 size_t multi_heap_get_allocated_size (int /*<<< orphan*/ ,void*) ; 

size_t heap_caps_get_allocated_size( void *ptr )
{
    heap_t *heap = find_containing_heap(ptr);
    size_t size = multi_heap_get_allocated_size(heap->heap, ptr);
    return size;
}