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
struct TYPE_3__ {size_t end; size_t start; int /*<<< orphan*/ * heap; } ;
typedef  TYPE_1__ heap_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_EARLY_LOGD (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 size_t HEAP_SIZE_MAX ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * multi_heap_register (void*,size_t) ; 

__attribute__((used)) static void register_heap(heap_t *region)
{
    size_t heap_size = region->end - region->start;
    assert(heap_size <= HEAP_SIZE_MAX);
    region->heap = multi_heap_register((void *)region->start, heap_size);
    if (region->heap != NULL) {
        ESP_EARLY_LOGD(TAG, "New heap initialised at %p", region->heap);
    }
}