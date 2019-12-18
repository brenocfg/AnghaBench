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
typedef  TYPE_1__* multi_heap_handle_t ;
typedef  int /*<<< orphan*/ * multi_heap_block_handle_t ;
typedef  int /*<<< orphan*/  heap_block_t ;
struct TYPE_4__ {int /*<<< orphan*/ * last_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_valid_block (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_next_block (int /*<<< orphan*/ *) ; 
 scalar_t__ is_free (int /*<<< orphan*/ *) ; 
 scalar_t__ is_last_block (int /*<<< orphan*/ *) ; 

multi_heap_block_handle_t multi_heap_get_next_block(multi_heap_handle_t heap, multi_heap_block_handle_t block)
{
    heap_block_t *next = get_next_block(block);
    /* check for valid free last block to avoid assert in assert_valid_block */
    if (next == heap->last_block && is_last_block(next) && is_free(next)) {
        return NULL;
    }
    assert_valid_block(heap, next);
    return next;
}