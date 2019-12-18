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
struct TYPE_4__ {int /*<<< orphan*/  setLocalCmds; int /*<<< orphan*/  subId; } ;
typedef  TYPE_1__ SubXactContext ;
typedef  int /*<<< orphan*/  SubTransactionId ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  CurTransactionContext ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  activeSetStmts ; 
 int /*<<< orphan*/  activeSubXactContexts ; 
 int /*<<< orphan*/  lcons (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeStringInfo () ; 
 TYPE_1__* palloc (int) ; 

__attribute__((used)) static void
PushSubXact(SubTransactionId subId)
{
	MemoryContext old_context = MemoryContextSwitchTo(CurTransactionContext);

	/* save provided subId as well as propagated SET LOCAL stmts */
	SubXactContext *state = palloc(sizeof(SubXactContext));
	state->subId = subId;
	state->setLocalCmds = activeSetStmts;

	/* append to list and reset active set stmts for upcoming sub-xact */
	activeSubXactContexts = lcons(state, activeSubXactContexts);
	activeSetStmts = makeStringInfo();

	MemoryContextSwitchTo(old_context);
}