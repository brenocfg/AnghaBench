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
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int /*<<< orphan*/ * NonSslList; } ;
struct TYPE_8__ {scalar_t__ EntryExpires; } ;
typedef  TYPE_1__ NON_SSL ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_2__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 scalar_t__ Tick64 () ; 

void DeleteOldNoSsl(CEDAR *c)
{
	UINT i;
	LIST *o;
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	o = NewListFast(NULL);

	for (i = 0;i < LIST_NUM(c->NonSslList);i++)
	{
		NON_SSL *n = LIST_DATA(c->NonSslList, i);

		if (n->EntryExpires <= Tick64())
		{
			Add(o, n);
		}
	}

	for (i = 0;i < LIST_NUM(o);i++)
	{
		NON_SSL *n = LIST_DATA(o, i);

		Delete(c->NonSslList, n);
		Free(n);
	}

	ReleaseList(o);
}