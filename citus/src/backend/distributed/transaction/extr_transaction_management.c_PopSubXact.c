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
struct TYPE_3__ {scalar_t__ subId; int /*<<< orphan*/  setLocalCmds; } ;
typedef  TYPE_1__ SubXactContext ;
typedef  scalar_t__ SubTransactionId ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CurTransactionContext ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  activeSetStmts ; 
 int /*<<< orphan*/  activeSubXactContexts ; 
 TYPE_1__* linitial (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_delete_first (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
PopSubXact(SubTransactionId subId)
{
	MemoryContext old_context = MemoryContextSwitchTo(CurTransactionContext);
	SubXactContext *state = linitial(activeSubXactContexts);

	/*
	 * the previous activeSetStmts is already invalid because it's in the now-
	 * aborted subxact (what we're popping), so no need to free before assign-
	 * ing with the setLocalCmds of the popped context
	 */
	Assert(state->subId == subId);
	activeSetStmts = state->setLocalCmds;
	activeSubXactContexts = list_delete_first(activeSubXactContexts);

	MemoryContextSwitchTo(old_context);
}