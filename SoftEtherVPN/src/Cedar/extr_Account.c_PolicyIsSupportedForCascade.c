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

bool PolicyIsSupportedForCascade(UINT i)
{
	if (i == 0 || i == 4 || i == 5 || i == 12 || i == 13 ||
		i == 14 || i == 19 || i == 20 || i == 21 || i == 26 || i == 30 || i == 31 || i == 36)
	{
		// These items are not supported by cascade connection.
		return false;
	}

	return true;
}