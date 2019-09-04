#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_12__ {int /*<<< orphan*/  CapsList; } ;
struct TYPE_11__ {scalar_t__ type; int num_value; TYPE_1__** values; scalar_t__ name; } ;
struct TYPE_10__ {int /*<<< orphan*/  elements; } ;
struct TYPE_9__ {int /*<<< orphan*/  IntValue; } ;
typedef  TYPE_2__ PACK ;
typedef  TYPE_3__ ELEMENT ;
typedef  TYPE_4__ CAPSLIST ;
typedef  int /*<<< orphan*/  CAPS ;

/* Variables and functions */
 int /*<<< orphan*/  CompareCaps ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewCaps (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewListFast (int /*<<< orphan*/ ) ; 
 scalar_t__ StartWith (scalar_t__,char*) ; 
 scalar_t__ VALUE_INT ; 
 int /*<<< orphan*/  Zero (TYPE_4__*,int) ; 

void InRpcCapsList(CAPSLIST *t, PACK *p)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(CAPSLIST));
	t->CapsList = NewListFast(CompareCaps);

	for (i = 0;i < LIST_NUM(p->elements);i++)
	{
		ELEMENT *e = LIST_DATA(p->elements, i);

		if (StartWith(e->name, "caps_") && e->type == VALUE_INT && e->num_value == 1)
		{
			CAPS *c = NewCaps(e->name + 5, e->values[0]->IntValue);
			Insert(t->CapsList, c);
		}
	}
}