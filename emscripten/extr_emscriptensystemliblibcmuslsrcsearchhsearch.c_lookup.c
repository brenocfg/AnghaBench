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
struct hsearch_data {TYPE_1__* __tab; } ;
struct TYPE_5__ {int /*<<< orphan*/  key; } ;
struct TYPE_4__ {size_t mask; TYPE_2__* entries; } ;
typedef  TYPE_2__ ENTRY ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ENTRY *lookup(char *key, size_t hash, struct hsearch_data *htab)
{
	size_t i, j;
	ENTRY *e;

	for (i=hash,j=1; ; i+=j++) {
		e = htab->__tab->entries + (i & htab->__tab->mask);
		if (!e->key || strcmp(e->key, key) == 0)
			break;
	}
	return e;
}