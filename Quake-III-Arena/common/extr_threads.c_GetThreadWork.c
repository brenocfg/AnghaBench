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

/* Variables and functions */
 int /*<<< orphan*/  ThreadLock () ; 
 int /*<<< orphan*/  ThreadUnlock () ; 
 int /*<<< orphan*/  _printf (char*,int) ; 
 int dispatch ; 
 int oldf ; 
 scalar_t__ pacifier ; 
 int workcount ; 

int	GetThreadWork (void)
{
	int	r;
	int	f;

	ThreadLock ();

	if (dispatch == workcount)
	{
		ThreadUnlock ();
		return -1;
	}

	f = 10*dispatch / workcount;
	if (f != oldf)
	{
		oldf = f;
		if (pacifier)
			_printf ("%i...", f);
	}

	r = dispatch;
	dispatch++;
	ThreadUnlock ();

	return r;
}