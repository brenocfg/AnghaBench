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
struct TYPE_9__ {scalar_t__ num_value; int /*<<< orphan*/  JsonHint_GroupName; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int /*<<< orphan*/  elements; int /*<<< orphan*/  CurrentJsonHint_GroupName; } ;
typedef  TYPE_1__ PACK ;
typedef  TYPE_2__ ELEMENT ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  FreeElement (TYPE_2__*) ; 
 scalar_t__ GetElement (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFINITE ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_ELEMENT_NUM ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

bool AddElement(PACK *p, ELEMENT *e)
{
	// Validate arguments
	if (p == NULL || e == NULL)
	{
		return false;
	}

	// Size Check
	if (LIST_NUM(p->elements) >= MAX_ELEMENT_NUM)
	{
		// Can not add any more
		FreeElement(e);
		return false;
	}

	// Check whether there is another item which have same name
	if (GetElement(p, e->name, INFINITE))
	{
		// Exists
		FreeElement(e);
		return false;
	}

	if (e->num_value == 0)
	{
		// VALUE without any items can not be added
		FreeElement(e);
		return false;
	}

	// Set JsonHint_GroupName
	StrCpy(e->JsonHint_GroupName, sizeof(e->JsonHint_GroupName), p->CurrentJsonHint_GroupName);

	// Adding
	Add(p->elements, e);
	return true;
}