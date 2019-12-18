#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  pendingInstances; TYPE_1__* currentPruningInstance; } ;
struct TYPE_8__ {TYPE_1__* instance; int /*<<< orphan*/ * continueAt; } ;
struct TYPE_7__ {int isPartial; } ;
typedef  TYPE_2__ PendingPruningInstance ;
typedef  int /*<<< orphan*/  OpExpr ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_3__ ClauseWalkerContext ;

/* Variables and functions */
 int /*<<< orphan*/  lappend (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* palloc0 (int) ; 

__attribute__((used)) static void
AddNewConjuction(ClauseWalkerContext *context, OpExpr *op)
{
	PendingPruningInstance *instance = palloc0(sizeof(PendingPruningInstance));

	instance->instance = context->currentPruningInstance;
	instance->continueAt = (Node *) op;

	/*
	 * Signal that this instance is not to be used for pruning on
	 * its own.  Once the pending instance is processed, it'll be
	 * used.
	 */
	instance->instance->isPartial = true;
	context->pendingInstances = lappend(context->pendingInstances, instance);
}