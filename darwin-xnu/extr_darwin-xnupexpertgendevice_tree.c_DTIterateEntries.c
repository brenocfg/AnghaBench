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
struct TYPE_5__ {int nChildren; } ;
struct TYPE_4__ {int currentIndex; int /*<<< orphan*/ * currentEntry; TYPE_2__* currentScope; } ;
typedef  TYPE_1__* DTEntryIterator ;
typedef  int /*<<< orphan*/ * DTEntry ;

/* Variables and functions */
 int /*<<< orphan*/ * GetFirstChild (TYPE_2__*) ; 
 int /*<<< orphan*/ * GetNextChild (int /*<<< orphan*/ *) ; 
 int kIterationDone ; 
 int kSuccess ; 

int
DTIterateEntries(DTEntryIterator iter, DTEntry *nextEntry)
{
	if (iter->currentIndex >= iter->currentScope->nChildren) {
		*nextEntry = NULL;
		return kIterationDone;
	} else {
		iter->currentIndex++;
		if (iter->currentIndex == 1) {
			iter->currentEntry = GetFirstChild(iter->currentScope);
		} else {
			iter->currentEntry = GetNextChild(iter->currentEntry);
		}
		*nextEntry = iter->currentEntry;
		return kSuccess;
	}
}