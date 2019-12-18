#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int size; int /*<<< orphan*/ * next; int /*<<< orphan*/ * prev; } ;
typedef  TYPE_1__ sh2rec_mem_block ;
struct TYPE_6__ {int /*<<< orphan*/ * next; } ;
typedef  TYPE_2__ sh2rec_mem_allocblock ;

/* Variables and functions */
 int SH2REC_MEM_INITIAL ; 
 TYPE_2__* allocblocks ; 
 int cur_allocation ; 
 TYPE_1__* freeblocks ; 
 scalar_t__ malloc (int) ; 

int sh2rec_mem_init(void) {
    sh2rec_mem_block *initblock;
    sh2rec_mem_allocblock *allocblock;
    uint8_t *block;

    /* Allocate our initial space for storing rec'd instructions in */
    block = (uint8_t *)malloc(SH2REC_MEM_INITIAL);

#ifdef DEBUG
    if(!block) {
        return -1;
    }
#endif

    /* Carve our structures out of the beginning of the block */
    allocblock = (sh2rec_mem_allocblock *)block;
    initblock = (sh2rec_mem_block *)(block + sizeof(sh2rec_mem_allocblock));
    cur_allocation = SH2REC_MEM_INITIAL;

    /* Fill in the rest of the structs */
    initblock->size = SH2REC_MEM_INITIAL - sizeof(sh2rec_mem_allocblock) -
        sizeof(sh2rec_mem_block);
    initblock->prev = NULL;
    initblock->next = NULL;

    allocblock->next = NULL;
    allocblocks = allocblock;

    /* The whole block is free, so put it in the free list */
    freeblocks = initblock;

    return 0;
}