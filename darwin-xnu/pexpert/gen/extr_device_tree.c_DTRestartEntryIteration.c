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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct DTSavedScope {int dummy; } ;
struct TYPE_5__ {scalar_t__ currentIndex; int /*<<< orphan*/ * currentEntry; int /*<<< orphan*/  outerScope; int /*<<< orphan*/  currentScope; TYPE_1__* savedScope; } ;
struct TYPE_4__ {struct TYPE_4__* nextScope; } ;
typedef  TYPE_1__* DTSavedScopePtr ;
typedef  TYPE_2__* DTEntryIterator ;

/* Variables and functions */
 int kSuccess ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ,int) ; 
 scalar_t__ outer ; 

int
DTRestartEntryIteration(DTEntryIterator iter)
{
#if 0
	// This commented out code allows a second argument (outer)
	// which (if true) causes restarting at the outer scope
	// rather than the current scope.
	DTSavedScopePtr scope;

	if (outer) {
		while ((scope = iter->savedScope) != NULL) {
			iter->savedScope = scope->nextScope;
			kfree((vm_offset_t) scope, sizeof(struct DTSavedScope));
		}
		iter->currentScope = iter->outerScope;
	}
#endif
	iter->currentEntry = NULL;
	iter->currentIndex = 0;
	return kSuccess;
}