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
struct TYPE_7__ {int numsides; TYPE_1__* sides; } ;
typedef  TYPE_2__ bspbrush_t ;
struct TYPE_6__ {scalar_t__ winding; } ;

/* Variables and functions */
 int /*<<< orphan*/  FreeMemory (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeWinding (scalar_t__) ; 
 scalar_t__ MemorySize (TYPE_2__*) ; 
 int /*<<< orphan*/  c_active_brushes ; 
 scalar_t__ c_brushmemory ; 
 int numthreads ; 

void FreeBrush (bspbrush_t *brushes)
{
	int			i;

	for (i=0 ; i<brushes->numsides ; i++)
		if (brushes->sides[i].winding)
			FreeWinding(brushes->sides[i].winding);
	if (numthreads == 1)
	{
		c_active_brushes--;
		c_brushmemory -= MemorySize(brushes);
		if (c_brushmemory < 0) c_brushmemory = 0;
	} //end if
	FreeMemory(brushes);
}