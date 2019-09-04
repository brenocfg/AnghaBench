#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  L3SwList; } ;
struct TYPE_11__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ L3SW ;
typedef  TYPE_2__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* L3GetSw (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 TYPE_1__* NewL3Sw (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  ReleaseL3Sw (TYPE_1__*) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

L3SW *L3AddSw(CEDAR *c, char *name)
{
	L3SW *s = NULL;
	// Validate arguments
	if (c == NULL || name == NULL)
	{
		return NULL;
	}

	LockList(c->L3SwList);
	{
		s = L3GetSw(c, name);

		if (s == NULL)
		{
			s = NewL3Sw(c, name);

			Insert(c->L3SwList, s);

			AddRef(s->ref);
		}
		else
		{
			ReleaseL3Sw(s);
			s = NULL;
		}
	}
	UnlockList(c->L3SwList);

	return s;
}