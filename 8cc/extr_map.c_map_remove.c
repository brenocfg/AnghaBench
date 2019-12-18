#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int size; int /*<<< orphan*/  nelem; int /*<<< orphan*/ ** val; int /*<<< orphan*/ ** key; } ;
typedef  TYPE_1__ Map ;

/* Variables and functions */
 int /*<<< orphan*/ * TOMBSTONE ; 
 int hash (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 

void map_remove(Map *m, char *key) {
    if (!m->key)
        return;
    int mask = m->size - 1;
    int i = hash(key) & mask;
    for (; m->key[i] != NULL; i = (i + 1) & mask) {
        if (m->key[i] == TOMBSTONE || strcmp(m->key[i], key))
            continue;
        m->key[i] = TOMBSTONE;
        m->val[i] = NULL;
        m->nelem--;
        return;
    }
}