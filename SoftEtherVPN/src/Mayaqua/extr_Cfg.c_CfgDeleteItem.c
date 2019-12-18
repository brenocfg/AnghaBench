#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* Name; struct TYPE_7__* Buf; TYPE_1__* Parent; } ;
struct TYPE_6__ {int /*<<< orphan*/  Items; } ;
typedef  TYPE_2__ ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 

void CfgDeleteItem(ITEM *t)
{
	// Validate arguments
	if (t == NULL)
	{
		return;
	}

	// Remove from the parent list
	Delete(t->Parent->Items, t);

	// Memory release
	Free(t->Buf);
	Free(t->Name);
	Free(t);
}