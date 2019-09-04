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
typedef  int UINT ;

/* Variables and functions */
 int MsEnableVLan (char*) ; 
 int /*<<< orphan*/  _exit (int) ; 

void enablevlan(UINT num, char **arg)
{
	bool ok;
	if (num < 1)
	{
		return;
	}

	ok = MsEnableVLan(arg[0]);

	if (ok == false)
	{
		_exit(1);
	}
	else
	{
		_exit(0);
	}
}