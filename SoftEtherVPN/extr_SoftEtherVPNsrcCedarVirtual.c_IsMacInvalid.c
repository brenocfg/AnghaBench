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
typedef  int UCHAR ;

/* Variables and functions */

bool IsMacInvalid(UCHAR *mac)
{
	UINT i;
	// Validate arguments
	if (mac == NULL)
	{
		return false;
	}

	for (i = 0;i < 6;i++)
	{
		if (mac[i] != 0x00)
		{
			return false;
		}
	}
	return true;
}