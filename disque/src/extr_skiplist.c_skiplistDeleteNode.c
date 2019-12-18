#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  backward; TYPE_1__* level; } ;
typedef  TYPE_4__ skiplistNode ;
struct TYPE_13__ {int level; int /*<<< orphan*/  length; TYPE_3__* header; int /*<<< orphan*/  tail; } ;
typedef  TYPE_5__ skiplist ;
struct TYPE_11__ {TYPE_2__* level; } ;
struct TYPE_10__ {int /*<<< orphan*/ * forward; } ;
struct TYPE_9__ {int span; TYPE_4__* forward; } ;

/* Variables and functions */

void skiplistDeleteNode(skiplist *sl, skiplistNode *x, skiplistNode **update) {
    int i;
    for (i = 0; i < sl->level; i++) {
        if (update[i]->level[i].forward == x) {
            update[i]->level[i].span += x->level[i].span - 1;
            update[i]->level[i].forward = x->level[i].forward;
        } else {
            update[i]->level[i].span -= 1;
        }
    }
    if (x->level[0].forward) {
        x->level[0].forward->backward = x->backward;
    } else {
        sl->tail = x->backward;
    }
    while(sl->level > 1 && sl->header->level[sl->level-1].forward == NULL)
        sl->level--;
    sl->length--;
}