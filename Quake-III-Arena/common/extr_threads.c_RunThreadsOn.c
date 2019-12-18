#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ qboolean ;

/* Variables and functions */
 int I_FloatTime () ; 
 int /*<<< orphan*/  _printf (char*,int) ; 
 scalar_t__ dispatch ; 
 int oldf ; 
 scalar_t__ pacifier ; 
 int workcount ; 

void RunThreadsOn (int workcnt, qboolean showpacifier, void(*func)(int))
{
	int		i;
	int		start, end;

	dispatch = 0;
	workcount = workcnt;
	oldf = -1;
	pacifier = showpacifier;
	start = I_FloatTime (); 
	func(0);

	end = I_FloatTime ();
	if (pacifier)
		_printf (" (%i)\n", end-start);
}