#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_9__ {struct TYPE_9__* next; void* value; struct TYPE_9__* name; } ;
typedef  TYPE_1__ ht_elt ;
struct TYPE_10__ {scalar_t__ num_buckets; scalar_t__ size; TYPE_1__** buckets; } ;
typedef  TYPE_2__ HT ;

/* Variables and functions */
 int /*<<< orphan*/  HT_expand (TYPE_2__*) ; 
 scalar_t__ eqstring (char const*,TYPE_1__*) ; 
 int hash_string (char const*) ; 
 int /*<<< orphan*/  xfree (TYPE_1__*) ; 
 TYPE_1__* xmalloc (int) ; 
 TYPE_1__* xstrdup (char const*) ; 

__attribute__((used)) static void *
HT_put(HT *ht, const char *name, void *value)
{
	uint32_t hc;
	size_t k;
	ht_elt *e, **prev;

	hc = hash_string(name);
	k = (size_t)(hc & ((uint32_t)ht->num_buckets - 1));
	prev = &ht->buckets[k];
	e = *prev;
	while (e != NULL) {
		if (eqstring(name, e->name)) {
			void *old_value;

			old_value = e->value;
			if (value == NULL) {
				*prev = e->next;
				xfree(e->name);
				xfree(e);
				ht->size --;
			} else {
				e->value = value;
			}
			return old_value;
		}
		prev = &e->next;
		e = *prev;
	}
	if (value != NULL) {
		e = xmalloc(sizeof *e);
		e->name = xstrdup(name);
		e->value = value;
		e->next = ht->buckets[k];
		ht->buckets[k] = e;
		ht->size ++;
		if (ht->size > ht->num_buckets) {
			HT_expand(ht);
		}
	}
	return NULL;
}