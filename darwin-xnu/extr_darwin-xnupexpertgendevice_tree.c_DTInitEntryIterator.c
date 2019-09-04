#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ currentIndex; int /*<<< orphan*/ * savedScope; int /*<<< orphan*/ * currentEntry; void* currentScope; void* outerScope; } ;
typedef  void* RealDTEntry ;
typedef  TYPE_1__* DTEntryIterator ;
typedef  int /*<<< orphan*/ * DTEntry ;

/* Variables and functions */
 int /*<<< orphan*/  DTInitialized ; 
 void* DTRootNode ; 
 int kError ; 
 int kSuccess ; 

int
DTInitEntryIterator(const DTEntry startEntry, DTEntryIterator iter)
{
	if (!DTInitialized) {
		return kError;
	}

	if (startEntry != NULL) {
		iter->outerScope = (RealDTEntry) startEntry;
		iter->currentScope = (RealDTEntry) startEntry;
	} else {
		iter->outerScope = DTRootNode;
		iter->currentScope = DTRootNode;
	}
	iter->currentEntry = NULL;
	iter->savedScope = NULL;
	iter->currentIndex = 0;

	return kSuccess;
}