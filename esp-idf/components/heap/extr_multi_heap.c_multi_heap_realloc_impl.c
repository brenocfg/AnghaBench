#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* multi_heap_handle_t ;
struct TYPE_26__ {void* data; } ;
typedef  TYPE_2__ heap_block_t ;
struct TYPE_25__ {size_t free_bytes; scalar_t__ minimum_free_bytes; } ;

/* Variables and functions */
 size_t ALIGN_UP (size_t) ; 
 int /*<<< orphan*/  MULTI_HEAP_ASSERT (int,TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_valid_block (TYPE_1__*,TYPE_2__*) ; 
 size_t block_data_size (TYPE_2__*) ; 
 TYPE_2__* get_block (void*) ; 
 TYPE_2__* get_next_block (TYPE_2__*) ; 
 TYPE_2__* get_prev_free_block (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ is_free (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/  memmove (void*,void*,size_t) ; 
 TYPE_2__* merge_adjacent (TYPE_1__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  multi_heap_free_impl (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  multi_heap_internal_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  multi_heap_internal_unlock (TYPE_1__*) ; 
 void* multi_heap_malloc_impl (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  split_if_necessary (TYPE_1__*,TYPE_2__*,size_t,int /*<<< orphan*/ *) ; 

void *multi_heap_realloc_impl(multi_heap_handle_t heap, void *p, size_t size)
{
    heap_block_t *pb = get_block(p);
    void *result;
    size = ALIGN_UP(size);

    assert(heap != NULL);

    if (p == NULL) {
        return multi_heap_malloc_impl(heap, size);
    }

    assert_valid_block(heap, pb);
    // non-null realloc arg should be allocated
    MULTI_HEAP_ASSERT(!is_free(pb), pb);

    if (size == 0) {
        /* note: calling multi_free_impl() here as we've already been
           through any poison-unwrapping */
        multi_heap_free_impl(heap, p);
        return NULL;
    }

    if (heap == NULL) {
        return NULL;
    }

    multi_heap_internal_lock(heap);
    result = NULL;

    if (size <= block_data_size(pb)) {
        // Shrinking....
        split_if_necessary(heap, pb, size, NULL);
        result = pb->data;
    }
    else if (heap->free_bytes < size - block_data_size(pb)) {
        // Growing, but there's not enough total free space in the heap
        multi_heap_internal_unlock(heap);
        return NULL;
    }

    // New size is larger than existing block
    if (result == NULL) {
        // See if we can grow into one or both adjacent blocks
        heap_block_t *orig_pb = pb;
        size_t orig_size = block_data_size(orig_pb);
        heap_block_t *next = get_next_block(pb);
        heap_block_t *prev = get_prev_free_block(heap, pb);

        // Can only grow into the previous free block if it's adjacent
        size_t prev_grow_size = (get_next_block(prev) == pb) ? block_data_size(prev) : 0;

        // Can grow into next block? (we may also need to grow into 'prev' to get to our desired size)
        if (is_free(next) && (block_data_size(pb) + block_data_size(next) + prev_grow_size >= size)) {
            pb = merge_adjacent(heap, pb, next);
        }

        // Can grow into previous block?
        // (try this even if we're already big enough from growing into 'next', as it reduces fragmentation)
        if (prev_grow_size > 0 && (block_data_size(pb) + prev_grow_size >= size)) {
            pb = merge_adjacent(heap, prev, pb);
            // this doesn't guarantee we'll be left with a big enough block, as it's
            // possible for the merge to fail if prev == heap->first_block
        }

        if (block_data_size(pb) >= size) {
            memmove(pb->data, orig_pb->data, orig_size);
            split_if_necessary(heap, pb, size, NULL);
            result = pb->data;
        }
    }

    if (result == NULL) {
        // Need to allocate elsewhere and copy data over
        //
        // (Calling _impl versions here as we've already been through any
        // unwrapping for heap poisoning features.)
        result = multi_heap_malloc_impl(heap, size);
        if (result != NULL) {
            memcpy(result, pb->data, block_data_size(pb));
            multi_heap_free_impl(heap, pb->data);
        }
    }

    if (heap->free_bytes < heap->minimum_free_bytes) {
        heap->minimum_free_bytes = heap->free_bytes;
    }

    multi_heap_internal_unlock(heap);
    return result;
}