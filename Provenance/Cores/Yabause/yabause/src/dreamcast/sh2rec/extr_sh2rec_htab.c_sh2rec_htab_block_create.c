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
typedef  void* u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_5__ {int length; int /*<<< orphan*/ * block; int /*<<< orphan*/ * ptr; void* pc; scalar_t__ cycles; void* start_pc; } ;
typedef  TYPE_1__ sh2rec_block_t ;
struct TYPE_6__ {TYPE_1__ block; struct TYPE_6__* next; } ;
typedef  TYPE_2__ htab_entry_t ;

/* Variables and functions */
 int hash_addr (void*) ; 
 scalar_t__ sh2rec_mem_alloc (int) ; 
 TYPE_2__** table ; 

sh2rec_block_t *sh2rec_htab_block_create(u32 addr, int length) {
    uint8_t *ptr;
    htab_entry_t *ent;
    int index = hash_addr(addr);

    ptr = (uint8_t *)sh2rec_mem_alloc(length + sizeof(htab_entry_t));

#ifdef DEBUG
    if(!ptr) {
        return NULL;
    }
#endif

    /* Allocate space for the block */
    ent = (htab_entry_t *)ptr;
    ent->block.block = (u16 *)(ptr + sizeof(htab_entry_t));

    /* Fill in the struct */
    ent->block.start_pc = addr;
    ent->block.cycles = 0;
    ent->block.pc = addr;
    ent->block.length = length;
    ent->block.ptr = ent->block.block;

    /* Put the item in the list (puts it at the head of the index in the table
       where it would go) */
    ent->next = table[index];
    table[index] = ent;

    return &ent->block;
}