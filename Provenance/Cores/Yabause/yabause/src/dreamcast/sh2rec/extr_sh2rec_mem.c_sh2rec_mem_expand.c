#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int size; } ;
struct TYPE_6__ {TYPE_2__* freespace; TYPE_1__ base; } ;
typedef  TYPE_3__ sh2rec_mem_usedblock ;
struct TYPE_5__ {int size; int ptr; } ;

/* Variables and functions */

int sh2rec_mem_expand(void *block, int amt) {
    sh2rec_mem_usedblock *b = (sh2rec_mem_usedblock *)block;

    /* If the freeblock has space, allow it */
    if(b->freespace->size > amt) {
        b->freespace->size -= amt;
        b->base.size += amt;
        b->freespace->ptr += amt;
        return 1;
    }

    return 0;
}