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
struct skiplistLevel {int dummy; } ;
struct TYPE_4__ {void* obj; } ;
typedef  TYPE_1__ skiplistNode ;

/* Variables and functions */
 TYPE_1__* zmalloc (int) ; 

skiplistNode *skiplistCreateNode(int level, void *obj) {
    skiplistNode *zn = zmalloc(sizeof(*zn)+level*sizeof(struct skiplistLevel));
    zn->obj = obj;
    return zn;
}