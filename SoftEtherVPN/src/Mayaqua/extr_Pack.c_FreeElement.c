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
typedef  size_t UINT ;
struct TYPE_5__ {size_t num_value; struct TYPE_5__* values; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ ELEMENT ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeValue (TYPE_1__,int /*<<< orphan*/ ) ; 

void FreeElement(ELEMENT *e)
{
	UINT i;
	// Validate arguments
	if (e == NULL)
	{
		return;
	}

	for (i = 0;i < e->num_value;i++)
	{
		FreeValue(e->values[i], e->type);
	}
	Free(e->values);

	Free(e);
}