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
typedef  int /*<<< orphan*/  uint32 ;
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ block; scalar_t__ ptr; } ;
typedef  TYPE_1__ sh2rec_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  icache_flush_range (int /*<<< orphan*/ ,scalar_t__) ; 
 int sh2rec_rec_inst (TYPE_1__*,int /*<<< orphan*/ ) ; 

int sh2rec_rec_block(sh2rec_block_t *b) {
    int done = 0;

    while(!done) {
        done = sh2rec_rec_inst(b, 0);
    }

    /* Flush the icache, so we don't execute stale data */
    icache_flush_range((uint32)b->block, ((u32)b->ptr) - ((u32)b->block));

    return 0;
}