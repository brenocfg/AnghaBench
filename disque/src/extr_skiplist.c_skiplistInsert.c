#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* backward; TYPE_1__* level; int /*<<< orphan*/  obj; } ;
typedef  TYPE_2__ skiplistNode ;
struct TYPE_9__ {int level; scalar_t__ (* compare ) (int /*<<< orphan*/ ,void*) ;unsigned int length; TYPE_2__* tail; TYPE_2__* header; } ;
typedef  TYPE_3__ skiplist ;
struct TYPE_7__ {unsigned int span; TYPE_2__* forward; } ;

/* Variables and functions */
 int SKIPLIST_MAXLEVEL ; 
 TYPE_2__* skiplistCreateNode (int,void*) ; 
 int skiplistRandomLevel () ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,void*) ; 

skiplistNode *skiplistInsert(skiplist *sl, void *obj) {
    skiplistNode *update[SKIPLIST_MAXLEVEL], *x;
    unsigned int rank[SKIPLIST_MAXLEVEL];
    int i, level;

    x = sl->header;
    for (i = sl->level-1; i >= 0; i--) {
        /* store rank that is crossed to reach the insert position */
        rank[i] = i == (sl->level-1) ? 0 : rank[i+1];
        while (x->level[i].forward &&
               sl->compare(x->level[i].forward->obj,obj) < 0)
        {
            rank[i] += x->level[i].span;
            x = x->level[i].forward;
        }
        update[i] = x;
    }

    /* If the element is already inside, return NULL. */
    if (x->level[0].forward &&
        sl->compare(x->level[0].forward->obj,obj) == 0) return NULL;

    /* Add a new node with a random number of levels. */
    level = skiplistRandomLevel();
    if (level > sl->level) {
        for (i = sl->level; i < level; i++) {
            rank[i] = 0;
            update[i] = sl->header;
            update[i]->level[i].span = sl->length;
        }
        sl->level = level;
    }
    x = skiplistCreateNode(level,obj);
    for (i = 0; i < level; i++) {
        x->level[i].forward = update[i]->level[i].forward;
        update[i]->level[i].forward = x;

        /* update span covered by update[i] as x is inserted here */
        x->level[i].span = update[i]->level[i].span - (rank[0] - rank[i]);
        update[i]->level[i].span = (rank[0] - rank[i]) + 1;
    }

    /* increment span for untouched levels */
    for (i = level; i < sl->level; i++) {
        update[i]->level[i].span++;
    }

    x->backward = (update[0] == sl->header) ? NULL : update[0];
    if (x->level[0].forward)
        x->level[0].forward->backward = x;
    else
        sl->tail = x;
    sl->length++;
    return x;
}