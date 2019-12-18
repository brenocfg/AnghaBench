#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  multi_heap_handle_t ;
typedef  int /*<<< orphan*/  heap_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  MULTI_HEAP_ASSERT (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert_valid_block (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t block_data_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_block (void*) ; 
 int /*<<< orphan*/  is_free (int /*<<< orphan*/ *) ; 

size_t multi_heap_get_allocated_size_impl(multi_heap_handle_t heap, void *p)
{
    heap_block_t *pb = get_block(p);

    assert_valid_block(heap, pb);
    MULTI_HEAP_ASSERT(!is_free(pb), pb); // block shouldn't be free
    return block_data_size(pb);
}