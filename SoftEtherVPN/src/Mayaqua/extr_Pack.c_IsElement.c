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
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int /*<<< orphan*/  elements; } ;
typedef  TYPE_1__ PACK ;
typedef  TYPE_2__ ELEMENT ;

/* Variables and functions */
 TYPE_2__* Search (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 

bool IsElement(PACK *p, char *name)
{
	ELEMENT t;
	ELEMENT *e;
	// Validate arguments
	if (p == NULL || name == NULL)
	{
		return false;
	}

	// Search
	StrCpy(t.name, sizeof(t.name), name);
	e = Search(p->elements, &t);

	if (e == NULL)
	{
		return false;
	}

	return true;
}