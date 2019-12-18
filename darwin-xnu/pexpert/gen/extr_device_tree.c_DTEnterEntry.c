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
struct DTSavedScope {int dummy; } ;
struct TYPE_5__ {scalar_t__ currentIndex; TYPE_1__* savedScope; int /*<<< orphan*/ * currentEntry; int /*<<< orphan*/ * currentScope; } ;
struct TYPE_4__ {scalar_t__ index; int /*<<< orphan*/ * entry; int /*<<< orphan*/ * scope; struct TYPE_4__* nextScope; } ;
typedef  TYPE_1__* DTSavedScopePtr ;
typedef  TYPE_2__* DTEntryIterator ;
typedef  int /*<<< orphan*/ * DTEntry ;

/* Variables and functions */
 int kError ; 
 int kSuccess ; 
 scalar_t__ kalloc (int) ; 

int
DTEnterEntry(DTEntryIterator iter, DTEntry childEntry)
{
	DTSavedScopePtr newScope;

	if (childEntry == NULL) {
		return kError;
	}
	newScope = (DTSavedScopePtr) kalloc(sizeof(struct DTSavedScope));
	newScope->nextScope = iter->savedScope;
	newScope->scope = iter->currentScope;
	newScope->entry = iter->currentEntry;
	newScope->index = iter->currentIndex;		

	iter->currentScope = childEntry;
	iter->currentEntry = NULL;
	iter->savedScope = newScope;
	iter->currentIndex = 0;

	return kSuccess;
}