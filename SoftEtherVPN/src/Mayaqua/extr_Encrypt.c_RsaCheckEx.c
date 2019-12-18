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
typedef  scalar_t__ UINT ;

/* Variables and functions */
 scalar_t__ RsaCheck () ; 
 int /*<<< orphan*/  SleepThread (int) ; 

bool RsaCheckEx()
{
	UINT num = 20;
	UINT i;

	for (i = 0;i < num;i++)
	{
		if (RsaCheck())
		{
			return true;
		}

		SleepThread(100);
	}

	return false;
}