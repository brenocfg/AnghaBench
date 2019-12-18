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
 int /*<<< orphan*/  Log_Print (char*) ; 
 scalar_t__ dispatch ; 
 int oldf ; 
 scalar_t__ pacifier ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 
 int workcount ; 

void RunThreadsOn(int workcnt, qboolean showpacifier, void(*func)(int))
{
	int start, end;

	Log_Print("no multi-threading\n");
	dispatch = 0;
	workcount = workcnt;
	oldf = -1;
	pacifier = showpacifier;
	start = I_FloatTime (); 
#ifdef NeXT
	if (pacifier)
		setbuf (stdout, NULL);
#endif
	func(0);

	end = I_FloatTime ();
	if (pacifier)
		printf (" (%i)\n", end-start);
}