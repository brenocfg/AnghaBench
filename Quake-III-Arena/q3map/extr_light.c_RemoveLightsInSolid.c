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
struct TYPE_4__ {struct TYPE_4__* next; scalar_t__ w; int /*<<< orphan*/  origin; } ;
typedef  TYPE_1__ light_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeWinding (scalar_t__) ; 
 scalar_t__ PointInSolid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _printf (char*,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* lights ; 

void RemoveLightsInSolid(void)
{
	light_t *light, *prev;
	int numsolid = 0;

	prev = NULL;
	for ( light = lights ; light ;  ) {
		if (PointInSolid(light->origin))
		{
			if (prev) prev->next = light->next;
			else lights = light->next;
			if (light->w)
				FreeWinding(light->w);
			free(light);
			numsolid++;
			if (prev)
				light = prev->next;
			else
				light = lights;
		}
		else
		{
			prev = light;
			light = light->next;
		}
	}
	_printf (" %7i lights in solid\n", numsolid);
}