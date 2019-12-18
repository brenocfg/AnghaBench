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
struct TYPE_4__ {int /*<<< orphan*/ * keyword; } ;
typedef  scalar_t__ Size ;
typedef  TYPE_1__ PQconninfoOption ;

/* Variables and functions */
 TYPE_1__* PQconndefaults () ; 
 int /*<<< orphan*/  PQconninfoFree (TYPE_1__*) ; 

__attribute__((used)) static Size
CalculateMaxSize()
{
	PQconninfoOption *defaults = PQconndefaults();
	PQconninfoOption *option = NULL;
	Size maxSize = 0;

	for (option = defaults;
		 option->keyword != NULL;
		 option++, maxSize++)
	{
		/* do nothing, we're just counting the elements */
	}

	PQconninfoFree(defaults);

	/* we've counted elements but libpq needs a final NULL, so add one */
	maxSize++;

	return maxSize;
}