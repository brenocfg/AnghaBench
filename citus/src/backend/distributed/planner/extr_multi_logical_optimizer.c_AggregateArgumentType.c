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
struct TYPE_4__ {scalar_t__ expr; } ;
typedef  TYPE_1__ TargetEntry ;
struct TYPE_5__ {int /*<<< orphan*/ * args; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_2__ Aggref ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  exprType (int /*<<< orphan*/ *) ; 
 scalar_t__ linitial (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Oid
AggregateArgumentType(Aggref *aggregate)
{
	List *argumentList = aggregate->args;
	TargetEntry *argument = (TargetEntry *) linitial(argumentList);
	Oid returnTypeId = exprType((Node *) argument->expr);

	/* Here we currently support aggregates with only one argument; assert that. */
	Assert(list_length(argumentList) == 1);

	return returnTypeId;
}