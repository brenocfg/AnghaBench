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
struct TYPE_4__ {int size; char** key; void** val; int /*<<< orphan*/  nused; int /*<<< orphan*/  nelem; } ;
typedef  TYPE_1__ Map ;

/* Variables and functions */
 char* TOMBSTONE ; 
 int hash (char*) ; 
 int /*<<< orphan*/  maybe_rehash (TYPE_1__*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

void map_put(Map *m, char *key, void *val) {
    maybe_rehash(m);
    int mask = m->size - 1;
    int i = hash(key) & mask;
    for (;; i = (i + 1) & mask) {
        char *k = m->key[i];
        if (k == NULL || k == TOMBSTONE) {
            m->key[i] = key;
            m->val[i] = val;
            m->nelem++;
            if (k == NULL)
                m->nused++;
            return;
        }
        if (!strcmp(k, key)) {
            m->val[i] = val;
            return;
        }
    }
}