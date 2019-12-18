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
struct TYPE_4__ {intptr_t header; } ;
typedef  TYPE_1__ heap_block_t ;

/* Variables and functions */
 intptr_t NEXT_BLOCK_MASK ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline heap_block_t *get_next_block(const heap_block_t *block)
{
    intptr_t next = block->header & NEXT_BLOCK_MASK;
    if (next == 0) {
        return NULL; /* last_block */
    }
    assert(next > (intptr_t)block);
    return (heap_block_t *)next;
}