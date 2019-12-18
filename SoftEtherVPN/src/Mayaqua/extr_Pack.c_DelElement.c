#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  elements; } ;
typedef  TYPE_1__ PACK ;
typedef  int /*<<< orphan*/  ELEMENT ;

/* Variables and functions */
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeElement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetElement (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFINITE ; 

void DelElement(PACK *p, char *name)
{
	ELEMENT *e;
	// Validate arguments
	if (p == NULL || name == NULL)
	{
		return;
	}

	e = GetElement(p, name, INFINITE);
	if (e != NULL)
	{
		Delete(p->elements, e);

		FreeElement(e);
	}
}