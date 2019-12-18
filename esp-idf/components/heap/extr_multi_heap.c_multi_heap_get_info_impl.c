#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ total_free_bytes; size_t largest_free_block; size_t total_allocated_bytes; int /*<<< orphan*/  minimum_free_bytes; int /*<<< orphan*/  allocated_blocks; int /*<<< orphan*/  free_blocks; int /*<<< orphan*/  total_blocks; } ;
typedef  TYPE_1__ multi_heap_info_t ;
typedef  TYPE_2__* multi_heap_handle_t ;
typedef  int /*<<< orphan*/  heap_block_t ;
struct TYPE_10__ {scalar_t__ free_bytes; int /*<<< orphan*/  minimum_free_bytes; int /*<<< orphan*/  first_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  MULTI_HEAP_ASSERT (int,TYPE_2__*) ; 
 size_t block_data_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_next_block (int /*<<< orphan*/ *) ; 
 scalar_t__ is_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_last_block (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  multi_heap_internal_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  multi_heap_internal_unlock (TYPE_2__*) ; 

void multi_heap_get_info_impl(multi_heap_handle_t heap, multi_heap_info_t *info)
{
    memset(info, 0, sizeof(multi_heap_info_t));

    if (heap == NULL) {
        return;
    }

    multi_heap_internal_lock(heap);
    for(heap_block_t *b = get_next_block(&heap->first_block); !is_last_block(b); b = get_next_block(b)) {
        info->total_blocks++;
        if (is_free(b)) {
            size_t s = block_data_size(b);
            info->total_free_bytes += s;
            if (s > info->largest_free_block) {
                info->largest_free_block = s;
            }
            info->free_blocks++;
        } else {
            info->total_allocated_bytes += block_data_size(b);
            info->allocated_blocks++;
        }
    }

    info->minimum_free_bytes = heap->minimum_free_bytes;
    // heap has wrong total size (address printed here is not indicative of the real error)
    MULTI_HEAP_ASSERT(info->total_free_bytes == heap->free_bytes, heap);

    multi_heap_internal_unlock(heap);

}