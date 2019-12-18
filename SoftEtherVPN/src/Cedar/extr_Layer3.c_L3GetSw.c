#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
struct TYPE_9__ {int /*<<< orphan*/  L3SwList; } ;
struct TYPE_8__ {int /*<<< orphan*/  ref; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ L3SW ;
typedef  TYPE_2__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 TYPE_1__* Search (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

L3SW *L3GetSw(CEDAR *c, char *name)
{
	L3SW t, *s;
	// Validate arguments
	if (c == NULL || name == NULL)
	{
		return NULL;
	}

	Zero(&t, sizeof(t));
	StrCpy(t.Name, sizeof(t.Name), name);

	LockList(c->L3SwList);
	{
		s = Search(c->L3SwList, &t);
	}
	UnlockList(c->L3SwList);

	if (s != NULL)
	{
		AddRef(s->ref);
	}

	return s;
}