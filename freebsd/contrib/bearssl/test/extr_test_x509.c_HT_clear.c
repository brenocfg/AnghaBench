#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* value; struct TYPE_5__* name; struct TYPE_5__* next; } ;
typedef  TYPE_1__ ht_elt ;
struct TYPE_6__ {size_t num_buckets; scalar_t__ size; TYPE_1__** buckets; } ;
typedef  TYPE_2__ HT ;

/* Variables and functions */
 int /*<<< orphan*/  xfree (TYPE_1__*) ; 

__attribute__((used)) static void
HT_clear(HT *ht, void (*free_value)(void *value))
{
	size_t u;

	for (u = 0; u < ht->num_buckets; u ++) {
		ht_elt *e, *f;

		f = NULL;
		for (e = ht->buckets[u]; e != NULL; e = f) {
			f = e->next;
			xfree(e->name);
			if (free_value != 0) {
				free_value(e->value);
			}
			xfree(e);
		}
		ht->buckets[u] = NULL;
	}
	ht->size = 0;
}