#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* obj; TYPE_1__* level; } ;
typedef  TYPE_2__ skiplistNode ;
struct TYPE_8__ {TYPE_2__* header; } ;
typedef  TYPE_3__ skiplist ;
struct TYPE_6__ {TYPE_2__* forward; } ;

/* Variables and functions */
 int /*<<< orphan*/  skiplistDelete (TYPE_3__*,void*) ; 

void *skiplistPopHead(skiplist *sl) {
    skiplistNode *x = sl->header;

    x = x->level[0].forward;
    if (!x) return NULL;
    void *ptr = x->obj;
    skiplistDelete(sl,ptr);
    return ptr;
}