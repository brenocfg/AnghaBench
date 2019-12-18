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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  size_t UINT ;

/* Variables and functions */
 size_t GetUniType (int /*<<< orphan*/ ) ; 
 size_t UniStrLen (int /*<<< orphan*/ *) ; 

UINT CalcUniToUtf8(wchar_t *s)
{
	UINT i, len, size;
	// Validate arguments
	if (s == NULL)
	{
		return 0;
	}

	size = 0;
	len = UniStrLen(s);
	for (i = 0;i < len;i++)
	{
		size += GetUniType(s[i]);
	}

	return size;
}