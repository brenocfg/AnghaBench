#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {void* value; int /*<<< orphan*/  name; struct TYPE_4__* next; } ;
typedef  TYPE_1__ ht_elt ;
struct TYPE_5__ {TYPE_1__** buckets; scalar_t__ num_buckets; } ;
typedef  TYPE_2__ HT ;

/* Variables and functions */
 scalar_t__ eqstring (char const*,int /*<<< orphan*/ ) ; 
 int hash_string (char const*) ; 

__attribute__((used)) static void *
HT_get(const HT *ht, const char *name)
{
	uint32_t hc;
	size_t k;
	ht_elt *e;

	hc = hash_string(name);
	k = (size_t)(hc & ((uint32_t)ht->num_buckets - 1));
	for (e = ht->buckets[k]; e != NULL; e = e->next) {
		if (eqstring(name, e->name)) {
			return e->value;
		}
	}
	return NULL;
}