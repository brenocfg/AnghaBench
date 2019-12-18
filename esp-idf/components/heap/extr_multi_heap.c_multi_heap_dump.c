#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* multi_heap_handle_t ;
struct TYPE_11__ {char* next_free; } ;
typedef  TYPE_2__ heap_block_t ;
struct TYPE_10__ {TYPE_2__ first_block; int /*<<< orphan*/  last_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  MULTI_HEAP_STDERR_PRINTF (char*,...) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_data_size (TYPE_2__*) ; 
 TYPE_2__* get_next_block (TYPE_2__*) ; 
 scalar_t__ is_free (TYPE_2__*) ; 
 int /*<<< orphan*/  multi_heap_internal_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  multi_heap_internal_unlock (TYPE_1__*) ; 

void multi_heap_dump(multi_heap_handle_t heap)
{
    assert(heap != NULL);

    multi_heap_internal_lock(heap);
    MULTI_HEAP_STDERR_PRINTF("Heap start %p end %p\nFirst free block %p\n", &heap->first_block, heap->last_block, heap->first_block.next_free);
    for(heap_block_t *b = &heap->first_block; b != NULL; b = get_next_block(b)) {
        MULTI_HEAP_STDERR_PRINTF("Block %p data size 0x%08x bytes next block %p", b, block_data_size(b), get_next_block(b));
        if (is_free(b)) {
            MULTI_HEAP_STDERR_PRINTF(" FREE. Next free %p\n", b->next_free);
        } else {
            MULTI_HEAP_STDERR_PRINTF("%s", "\n"); /* C macros & optional __VA_ARGS__ */
        }
    }
    multi_heap_internal_unlock(heap);
}