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
typedef  scalar_t__ u32 ;
struct TYPE_5__ {scalar_t__ start_pc; } ;
struct TYPE_6__ {struct TYPE_6__* next; TYPE_1__ block; } ;
typedef  TYPE_2__ htab_entry_t ;

/* Variables and functions */
 int hash_addr (scalar_t__) ; 
 int /*<<< orphan*/  sh2rec_mem_free (TYPE_2__*) ; 
 TYPE_2__** table ; 

void sh2rec_htab_block_remove(u32 addr) {
    int index = hash_addr(addr);
    htab_entry_t *i, *tmp, *last;

    i = table[index];
    last = NULL;

    /* Look through everything for the entry we're supposed to remove */
    while(i) {
        tmp = i->next;

        /* Is this the entry we're looking for? */
        if(i->block.start_pc == addr) {
            /* Unhook the entry from the list */
            if(last) {
                last->next = tmp;
            }
            else {
                table[index] = tmp;
            }

            /* Free any memory used by the block */
            sh2rec_mem_free(i);

            return;
        }

        last = i;
        i = tmp;
    }
}