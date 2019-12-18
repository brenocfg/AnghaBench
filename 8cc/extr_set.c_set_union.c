#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  v; struct TYPE_8__* next; } ;
typedef  TYPE_1__ Set ;

/* Variables and functions */
 TYPE_1__* set_add (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_has (TYPE_1__*,int /*<<< orphan*/ ) ; 

Set *set_union(Set *a, Set *b) {
    Set *r = b;
    for (; a; a = a->next)
        if (!set_has(b, a->v))
            r = set_add(r, a->v);
    return r;
}