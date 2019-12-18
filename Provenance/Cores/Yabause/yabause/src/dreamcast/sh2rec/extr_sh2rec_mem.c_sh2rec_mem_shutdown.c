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
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ sh2rec_mem_allocblock ;

/* Variables and functions */
 TYPE_1__* allocblocks ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/ * freeblocks ; 
 int /*<<< orphan*/ * usedblocks ; 

void sh2rec_mem_shutdown(void) {
    sh2rec_mem_allocblock *i, *tmp;

    /* Loop through and free any blocks we allocated */
    i = allocblocks;
    while(i) {
        tmp = i->next;
        free(i);
        i = tmp;
    }

    /* Clean up the stale pointers */
    allocblocks = NULL;
    freeblocks = NULL;
    usedblocks = NULL;
}