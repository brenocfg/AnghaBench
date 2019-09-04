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
 int IsWordChar (scalar_t__) ; 

UINT GetNextWordWidth(wchar_t *str)
{
	UINT i;
	UINT ret;
	// Validate arguments
	if (str == NULL)
	{
		return 0;
	}

	ret = 0;

	for (i = 0;;i++)
	{
		wchar_t c = str[i];

		if (c == 0)
		{
			break;
		}

		if (IsWordChar(c) == false)
		{
			break;
		}

		ret++;
	}

	return ret;
}