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
struct TYPE_6__ {unsigned int namehash; int /*<<< orphan*/  name; struct TYPE_6__* next; } ;
struct TYPE_5__ {unsigned int mask; TYPE_2__** bucketPtr; } ;
typedef  TYPE_1__ Hash_Table ;
typedef  TYPE_2__ Hash_Entry ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

Hash_Entry *
Hash_FindEntry(Hash_Table *t, const char *key)
{
	Hash_Entry *e;
	unsigned h;
	const char *p;

	if (t == NULL || t->bucketPtr == NULL) {
	    return NULL;
	}
	for (h = 0, p = key; *p;)
		h = (h << 5) - h + *p++;
	p = key;
	for (e = t->bucketPtr[h & t->mask]; e != NULL; e = e->next)
		if (e->namehash == h && strcmp(e->name, p) == 0)
			return (e);
	return NULL;
}