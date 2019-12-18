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
typedef  int /*<<< orphan*/  winding_t ;
struct TYPE_4__ {int /*<<< orphan*/ * winding; } ;
typedef  TYPE_1__ portal_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FreeWinding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OutputWinding (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PortalVisibleSides (TYPE_1__*) ; 
 int /*<<< orphan*/ * ReverseWinding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_glfaces ; 

void OutputPortal (portal_t *p, FILE *glview)
{
	winding_t	*w;
	int		sides;

	sides = PortalVisibleSides (p);
	if (!sides)
		return;

	c_glfaces++;

	w = p->winding;

	if (sides == 2)		// back side
		w = ReverseWinding (w);

	OutputWinding (w, glview);

	if (sides == 2)
		FreeWinding(w);
}