#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {struct TYPE_15__* next; int /*<<< orphan*/  key; } ;
typedef  TYPE_2__ dictEntry ;
struct TYPE_16__ {TYPE_1__* ht; } ;
typedef  TYPE_3__ dict ;
struct TYPE_14__ {scalar_t__ size; unsigned int sizemask; int /*<<< orphan*/  used; TYPE_2__** table; } ;

/* Variables and functions */
 int DICT_ERR ; 
 int DICT_OK ; 
 int /*<<< orphan*/  _dictRehashStep (TYPE_3__*) ; 
 scalar_t__ dictCompareKeys (TYPE_3__*,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictFreeKey (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  dictFreeVal (TYPE_3__*,TYPE_2__*) ; 
 unsigned int dictHashKey (TYPE_3__*,void const*) ; 
 scalar_t__ dictIsRehashing (TYPE_3__*) ; 
 int /*<<< orphan*/  zfree (TYPE_2__*) ; 

__attribute__((used)) static int dictGenericDelete(dict *d, const void *key, int nofree)
{
    unsigned int h, idx;
    dictEntry *he, *prevHe;
    int table;

    if (d->ht[0].size == 0) return DICT_ERR; /* d->ht[0].table is NULL */
    if (dictIsRehashing(d)) _dictRehashStep(d);
    h = dictHashKey(d, key);

    for (table = 0; table <= 1; table++) {
        idx = h & d->ht[table].sizemask;
        he = d->ht[table].table[idx];
        prevHe = NULL;
        while(he) {
            if (dictCompareKeys(d, key, he->key)) {
                /* Unlink the element from the list */
                if (prevHe)
                    prevHe->next = he->next;
                else
                    d->ht[table].table[idx] = he->next;
                if (!nofree) {
                    dictFreeKey(d, he);
                    dictFreeVal(d, he);
                }
                zfree(he);
                d->ht[table].used--;
                return DICT_OK;
            }
            prevHe = he;
            he = he->next;
        }
        if (!dictIsRehashing(d)) break;
    }
    return DICT_ERR; /* not found */
}