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
struct TYPE_5__ {scalar_t__ winding; } ;
typedef  TYPE_1__ portal_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeMemory (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeWinding (scalar_t__) ; 
 scalar_t__ MemorySize (TYPE_1__*) ; 
 int /*<<< orphan*/  c_active_portals ; 
 int /*<<< orphan*/  c_portalmemory ; 
 int numthreads ; 

void FreePortal (portal_t *p)
{
	if (p->winding) FreeWinding(p->winding);
	if (numthreads == 1)
	{
		c_active_portals--;
		c_portalmemory -= MemorySize(p);
	} //end if
	FreeMemory(p);
}