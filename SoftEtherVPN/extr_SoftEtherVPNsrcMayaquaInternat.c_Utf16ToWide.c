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
typedef  scalar_t__ USHORT ;
typedef  size_t UINT ;

/* Variables and functions */
 scalar_t__* Malloc (size_t) ; 

wchar_t *Utf16ToWide(USHORT *str)
{
	wchar_t *ret;
	UINT len, i;
	// Validate arguments
	if (str == NULL)
	{
		return NULL;
	}

	len = 0;
	while (true)
	{
		if (str[len] == 0)
		{
			break;
		}
		len++;
	}

	ret = Malloc((len + 1) * sizeof(wchar_t));
	for (i = 0;i < len + 1;i++)
	{
		ret[i] = (wchar_t)str[i];
	}

	return ret;
}