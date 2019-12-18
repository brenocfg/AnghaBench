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
typedef  TYPE_1__ sh2rec_block_t ;
struct TYPE_6__ {struct TYPE_6__* next; TYPE_1__ block; } ;
typedef  TYPE_2__ htab_entry_t ;

/* Variables and functions */
 size_t hash_addr (scalar_t__) ; 
 TYPE_2__** table ; 

sh2rec_block_t *sh2rec_htab_lookup(u32 addr) {
    htab_entry_t *i = table[hash_addr(addr)];

    /* Look through the chain for the entry we're after */
    while(i) {
        if(i->block.start_pc == addr) {
            return &i->block;
        }

        i = i->next;
    }

    /* Didn't find it, punt. */
    return NULL;
}