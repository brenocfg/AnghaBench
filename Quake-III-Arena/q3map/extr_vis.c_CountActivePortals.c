#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ hint; scalar_t__ removed; } ;
typedef  TYPE_1__ vportal_t ;

/* Variables and functions */
 int /*<<< orphan*/  _printf (char*,int) ; 
 int numportals ; 
 TYPE_1__* portals ; 

int CountActivePortals(void)
{
	int num, hints, j;
	vportal_t *p;

	num = 0;
	hints = 0;
	for (j = 0; j < numportals * 2; j++)
	{
		p = portals + j;
		if (p->removed)
			continue;
		if (p->hint)
			hints++;
		num++;
	}
	_printf("%6d active portals\n", num);
	_printf("%6d hint portals\n", hints);
	return num;
}