#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  obj; TYPE_1__* level; } ;
typedef  TYPE_2__ skiplistNode ;
struct TYPE_11__ {int level; scalar_t__ (* compare ) (int /*<<< orphan*/ ,void*) ;TYPE_2__* header; } ;
typedef  TYPE_3__ skiplist ;
struct TYPE_9__ {TYPE_2__* forward; } ;

/* Variables and functions */
 int SKIPLIST_MAXLEVEL ; 
 int /*<<< orphan*/  skiplistDeleteNode (TYPE_3__*,TYPE_2__*,TYPE_2__**) ; 
 int /*<<< orphan*/  skiplistFreeNode (TYPE_2__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,void*) ; 

int skiplistDelete(skiplist *sl, void *obj) {
    skiplistNode *update[SKIPLIST_MAXLEVEL], *x;
    int i;

    x = sl->header;
    for (i = sl->level-1; i >= 0; i--) {
        while (x->level[i].forward &&
               sl->compare(x->level[i].forward->obj,obj) < 0)
        {
            x = x->level[i].forward;
        }
        update[i] = x;
    }
    x = x->level[0].forward;
    if (x && sl->compare(x->obj,obj) == 0) {
        skiplistDeleteNode(sl, x, update);
        skiplistFreeNode(x);
        return 1;
    }
    return 0; /* not found */
}