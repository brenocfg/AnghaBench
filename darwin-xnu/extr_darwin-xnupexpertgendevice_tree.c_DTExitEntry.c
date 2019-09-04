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
struct DTSavedScope {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  currentEntry; int /*<<< orphan*/  currentIndex; int /*<<< orphan*/  currentScope; TYPE_1__* savedScope; } ;
struct TYPE_5__ {int /*<<< orphan*/  index; int /*<<< orphan*/  entry; int /*<<< orphan*/  scope; struct TYPE_5__* nextScope; } ;
typedef  TYPE_1__* DTSavedScopePtr ;
typedef  TYPE_2__* DTEntryIterator ;
typedef  int /*<<< orphan*/  DTEntry ;

/* Variables and functions */
 int kError ; 
 int kSuccess ; 
 int /*<<< orphan*/  kfree (TYPE_1__*,int) ; 

int
DTExitEntry(DTEntryIterator iter, DTEntry *currentPosition)
{
	DTSavedScopePtr newScope;

	newScope = iter->savedScope;
	if (newScope == NULL) {
		return kError;
	}
	iter->savedScope = newScope->nextScope;
	iter->currentScope = newScope->scope;
	iter->currentEntry = newScope->entry;
	iter->currentIndex = newScope->index;
	*currentPosition = iter->currentEntry;

	kfree(newScope, sizeof(struct DTSavedScope));

	return kSuccess;
}