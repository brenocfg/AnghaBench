#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ht_elt ;
struct TYPE_7__ {size_t num_buckets; TYPE_1__** buckets; } ;
typedef  TYPE_2__ HT ;

/* Variables and functions */
 int hash_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (TYPE_1__**) ; 
 TYPE_1__** xmalloc (size_t) ; 

__attribute__((used)) static void
HT_expand(HT *ht)
{
	size_t n, n2, u;
	ht_elt **new_buckets;

	n = ht->num_buckets;
	n2 = n << 1;
	new_buckets = xmalloc(n2 * sizeof *new_buckets);
	for (u = 0; u < n2; u ++) {
		new_buckets[u] = NULL;
	}
	for (u = 0; u < n; u ++) {
		ht_elt *e, *f;

		f = NULL;
		for (e = ht->buckets[u]; e != NULL; e = f) {
			uint32_t hc;
			size_t v;

			hc = hash_string(e->name);
			v = (size_t)(hc & ((uint32_t)n2 - 1));
			f = e->next;
			e->next = new_buckets[v];
			new_buckets[v] = e;
		}
	}
	xfree(ht->buckets);
	ht->buckets = new_buckets;
	ht->num_buckets = n2;
}