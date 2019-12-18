#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ irqvectptr ;
struct TYPE_2__ {int /*<<< orphan*/ * v; } ;

/* Variables and functions */
 TYPE_1__* etrax_irv ; 

void
set_break_vector(int n, irqvectptr addr)
{
	unsigned short *jinstr = (unsigned short *)&etrax_irv->v[n*2];
	unsigned long *jaddr = (unsigned long *)(jinstr + 1);

	/* if you don't know what this does, do not touch it! */
	
	*jinstr = 0x0d3f;
	*jaddr = (unsigned long)addr;

	/* 00000026 <clrlop+1a> 3f0d82000000     jump  0x82 */
}