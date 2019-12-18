#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* next; } ;
struct TYPE_7__ {scalar_t__ nextIndex; TYPE_3__* hashEntryPtr; TYPE_1__* tablePtr; } ;
struct TYPE_6__ {scalar_t__ size; TYPE_3__** bucketPtr; } ;
typedef  TYPE_1__ Hash_Table ;
typedef  TYPE_2__ Hash_Search ;
typedef  TYPE_3__ Hash_Entry ;

/* Variables and functions */

Hash_Entry *
Hash_EnumNext(Hash_Search *searchPtr)
{
	Hash_Entry *e;
	Hash_Table *t = searchPtr->tablePtr;

	/*
	 * The hashEntryPtr field points to the most recently returned
	 * entry, or is nil if we are starting up.  If not nil, we have
	 * to start at the next one in the chain.
	 */
	e = searchPtr->hashEntryPtr;
	if (e != NULL)
		e = e->next;
	/*
	 * If the chain ran out, or if we are starting up, we need to
	 * find the next nonempty chain.
	 */
	while (e == NULL) {
		if (searchPtr->nextIndex >= t->size)
			return NULL;
		e = t->bucketPtr[searchPtr->nextIndex++];
	}
	searchPtr->hashEntryPtr = e;
	return (e);
}