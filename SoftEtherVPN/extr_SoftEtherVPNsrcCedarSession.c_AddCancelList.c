#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_5__ {int /*<<< orphan*/  ref; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ CANCEL ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 

void AddCancelList(LIST *o, CANCEL *c)
{
	UINT i;
	// Validate arguments
	if (o == NULL || c == NULL)
	{
		return;
	}

	for (i = 0;i < LIST_NUM(o);i++)
	{
		CANCEL *t = LIST_DATA(o, i);
		if (t == c)
		{
			return;
		}
	}

	AddRef(c->ref);
	Add(o, c);
}