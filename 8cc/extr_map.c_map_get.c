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
struct TYPE_4__ {struct TYPE_4__* parent; } ;
typedef  TYPE_1__ Map ;

/* Variables and functions */
 void* map_get_nostack (TYPE_1__*,char*) ; 

void *map_get(Map *m, char *key) {
    void *r = map_get_nostack(m, key);
    if (r)
        return r;
    // Map is stackable. If no value is found,
    // continue searching from the parent.
    if (m->parent)
        return map_get(m->parent, key);
    return NULL;
}