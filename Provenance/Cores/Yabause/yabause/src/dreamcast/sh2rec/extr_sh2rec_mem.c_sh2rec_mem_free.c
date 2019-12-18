#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int size; TYPE_1__* prev; TYPE_4__* next; } ;
struct TYPE_10__ {TYPE_2__ base; int /*<<< orphan*/ * freespace; } ;
typedef  TYPE_3__ sh2rec_mem_usedblock ;
struct TYPE_11__ {TYPE_1__* prev; } ;
typedef  TYPE_4__ sh2rec_mem_block ;
struct TYPE_8__ {TYPE_4__* next; } ;

/* Variables and functions */
 TYPE_4__* freeblocks ; 
 TYPE_3__* usedblocks ; 
 TYPE_3__* usedblocks_tail ; 

void sh2rec_mem_free(void *block) {
    sh2rec_mem_usedblock *b = (sh2rec_mem_usedblock *)block;

    /* Remove the usedblock from the chain */
    if(b->base.next) {
        b->base.next->prev = b->base.prev;
    }

    if(b->base.prev) {
        b->base.prev->next = b->base.next;
    }

    if(b == usedblocks) {
        usedblocks = (sh2rec_mem_usedblock *)b->base.next;
    }

    if(b == usedblocks_tail) {
        usedblocks_tail = (sh2rec_mem_usedblock *)b->base.prev;
    }

    /* Treat the usedblock like its a freeblock (it is an extension of the
       freeblock), and just link it into the free blocks list */
    b->freespace = NULL;
    b->base.next = freeblocks;
    b->base.prev = NULL;
    b->base.size += sizeof(sh2rec_mem_usedblock) - sizeof(sh2rec_mem_block);
    freeblocks = (sh2rec_mem_block *)b;
}