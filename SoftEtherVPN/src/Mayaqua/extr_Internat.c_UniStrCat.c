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
typedef  int UINT ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (scalar_t__*,scalar_t__*,int) ; 
 int UniStrLen (scalar_t__*) ; 
 int /*<<< orphan*/  wcscpy (scalar_t__*,char*) ; 

UINT UniStrCat(wchar_t *dst, UINT size, wchar_t *src)
{
	UINT len1, len2, len_test;
	// Validate arguments
	if (dst == NULL || src == NULL)
	{
		return 0;
	}
	if (size != 0 && size < sizeof(wchar_t))
	{
		return 0;
	}
	if (size == sizeof(wchar_t))
	{
		wcscpy(dst, L"");
		return 0;
	}
	if (size == 0)
	{
		// Ignore the length
		size = 0x3fffffff;
	}

	len1 = UniStrLen(dst);
	len2 = UniStrLen(src);
	len_test = len1 + len2 + 1;
	if (len_test > (size / sizeof(wchar_t)))
	{
		if (len2 <= (len_test - (size / sizeof(wchar_t))))
		{
			return 0;
		}
		len2 -= len_test - (size / sizeof(wchar_t));
	}
	Copy(&dst[len1], src, len2 * sizeof(wchar_t));
	dst[len1 + len2] = 0;

	return len1 + len2;
}