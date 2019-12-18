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
struct TYPE_5__ {TYPE_2__* block; } ;
struct TYPE_6__ {TYPE_1__ block; struct TYPE_6__* next; } ;
typedef  TYPE_2__ htab_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static void htab_free_chain(htab_entry_t *ent) {
    htab_entry_t *i, *tmp;

    i = ent;
    while(i) {
        tmp = i->next;
        free(i->block.block);
        free(i);
        i = tmp;
    }
}