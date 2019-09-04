#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int level; int (* compare ) (void const*,void const*) ;int /*<<< orphan*/ * tail; TYPE_4__* header; scalar_t__ length; } ;
typedef  TYPE_2__ skiplist ;
struct TYPE_8__ {int /*<<< orphan*/ * backward; TYPE_1__* level; } ;
struct TYPE_6__ {scalar_t__ span; int /*<<< orphan*/ * forward; } ;

/* Variables and functions */
 int SKIPLIST_MAXLEVEL ; 
 TYPE_4__* skiplistCreateNode (int,int /*<<< orphan*/ *) ; 
 TYPE_2__* zmalloc (int) ; 

skiplist *skiplistCreate(int (*compare)(const void *, const void *)) {
    int j;
    skiplist *sl;

    sl = zmalloc(sizeof(*sl));
    sl->level = 1;
    sl->length = 0;
    sl->header = skiplistCreateNode(SKIPLIST_MAXLEVEL,NULL);
    for (j = 0; j < SKIPLIST_MAXLEVEL; j++) {
        sl->header->level[j].forward = NULL;
        sl->header->level[j].span = 0;
    }
    sl->header->backward = NULL;
    sl->tail = NULL;
    sl->compare = compare;
    return sl;
}