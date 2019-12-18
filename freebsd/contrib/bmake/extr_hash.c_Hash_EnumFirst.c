#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * hashEntryPtr; scalar_t__ nextIndex; int /*<<< orphan*/ * tablePtr; } ;
typedef  int /*<<< orphan*/  Hash_Table ;
typedef  TYPE_1__ Hash_Search ;
typedef  int /*<<< orphan*/  Hash_Entry ;

/* Variables and functions */
 int /*<<< orphan*/ * Hash_EnumNext (TYPE_1__*) ; 

Hash_Entry *
Hash_EnumFirst(Hash_Table *t, Hash_Search *searchPtr)
{
	searchPtr->tablePtr = t;
	searchPtr->nextIndex = 0;
	searchPtr->hashEntryPtr = NULL;
	return Hash_EnumNext(searchPtr);
}