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
struct TYPE_3__ {scalar_t__ header; } ;
typedef  TYPE_1__ heap_block_t ;

/* Variables and functions */
 intptr_t NEXT_BLOCK_MASK ; 

__attribute__((used)) static inline size_t block_data_size(const heap_block_t *block)
{
    intptr_t next = (intptr_t)block->header & NEXT_BLOCK_MASK;
    intptr_t this = (intptr_t)block;
    if (next == 0) {
        return 0; /* this is the last block in the heap */
    }
    return next - this - sizeof(block->header);
}