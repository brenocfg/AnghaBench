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
struct TYPE_3__ {int header; } ;
typedef  TYPE_1__ heap_block_t ;

/* Variables and functions */
 int NEXT_BLOCK_MASK ; 

__attribute__((used)) static inline bool is_last_block(const heap_block_t *block)
{
    return (block->header & NEXT_BLOCK_MASK) == 0;
}