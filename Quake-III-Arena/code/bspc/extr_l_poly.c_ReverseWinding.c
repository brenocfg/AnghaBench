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
struct TYPE_5__ {int numpoints; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ winding_t ;

/* Variables and functions */
 TYPE_1__* AllocWinding (int) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

winding_t	*ReverseWinding (winding_t *w)
{
	int			i;
	winding_t	*c;

	c = AllocWinding (w->numpoints);
	for (i=0 ; i<w->numpoints ; i++)
	{
		VectorCopy (w->p[w->numpoints-1-i], c->p[i]);
	}
	c->numpoints = w->numpoints;
	return c;
}