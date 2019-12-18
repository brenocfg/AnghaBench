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
typedef  scalar_t__ wchar_t ;
typedef  size_t UINT ;

/* Variables and functions */
 size_t UniStrLen (scalar_t__*) ; 

bool UniInChar(wchar_t *string, wchar_t c)
{
	UINT i, len;
	// Validate arguments
	if (string == NULL)
	{
		return false;
	}

	len = UniStrLen(string);

	for (i = 0;i < len;i++)
	{
		if (string[i] == c)
		{
			return true;
		}
	}

	return false;
}