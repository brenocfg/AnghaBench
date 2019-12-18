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
struct TYPE_3__ {char** key; void** val; int size; double nused; double nelem; } ;
typedef  TYPE_1__ Map ;

/* Variables and functions */
 int INIT_SIZE ; 
 char* TOMBSTONE ; 
 void* calloc (int,int) ; 
 int hash (char*) ; 

__attribute__((used)) static void maybe_rehash(Map *m) {
    if (!m->key) {
        m->key = calloc(INIT_SIZE, sizeof(char *));
        m->val = calloc(INIT_SIZE, sizeof(void *));
        m->size = INIT_SIZE;
        return;
    }
    if (m->nused < m->size * 0.7)
        return;
    int newsize = (m->nelem < m->size * 0.35) ? m->size : m->size * 2;
    char **k = calloc(newsize, sizeof(char *));
    void **v = calloc(newsize, sizeof(void *));
    int mask = newsize - 1;
    for (int i = 0; i < m->size; i++) {
        if (m->key[i] == NULL || m->key[i] == TOMBSTONE)
            continue;
        int j = hash(m->key[i]) & mask;
        for (;; j = (j + 1) & mask) {
            if (k[j] != NULL)
                continue;
            k[j] = m->key[i];
            v[j] = m->val[i];
            break;
        }
    }
    m->key = k;
    m->val = v;
    m->size = newsize;
    m->nused = m->nelem;
}