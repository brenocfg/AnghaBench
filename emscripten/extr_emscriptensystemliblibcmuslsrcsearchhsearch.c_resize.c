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
struct hsearch_data {TYPE_1__* __tab; } ;
struct TYPE_6__ {scalar_t__ key; } ;
struct TYPE_5__ {int mask; TYPE_2__* entries; } ;
typedef  TYPE_2__ ENTRY ;

/* Variables and functions */
 size_t MAXSIZE ; 
 size_t MINSIZE ; 
 TYPE_2__* calloc (size_t,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 size_t keyhash (scalar_t__) ; 

__attribute__((used)) static int resize(size_t nel, struct hsearch_data *htab)
{
	size_t newsize;
	size_t i, j;
	ENTRY *e, *newe;
	ENTRY *oldtab = htab->__tab->entries;
	ENTRY *oldend = htab->__tab->entries + htab->__tab->mask + 1;

	if (nel > MAXSIZE)
		nel = MAXSIZE;
	for (newsize = MINSIZE; newsize < nel; newsize *= 2);
	htab->__tab->entries = calloc(newsize, sizeof *htab->__tab->entries);
	if (!htab->__tab->entries) {
		htab->__tab->entries = oldtab;
		return 0;
	}
	htab->__tab->mask = newsize - 1;
	if (!oldtab)
		return 1;
	for (e = oldtab; e < oldend; e++)
		if (e->key) {
			for (i=keyhash(e->key),j=1; ; i+=j++) {
				newe = htab->__tab->entries + (i & htab->__tab->mask);
				if (!newe->key)
					break;
			}
			*newe = *e;
		}
	free(oldtab);
	return 1;
}