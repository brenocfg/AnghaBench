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

/* Variables and functions */
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * UniCopyStr (int /*<<< orphan*/ *) ; 
 scalar_t__ UniStrLen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniTrim (int /*<<< orphan*/ *) ; 

bool IsEmptyUniStr(wchar_t *str)
{
	bool ret;
	wchar_t *s;
	// Validate arguments
	if (str == NULL)
	{
		return true;
	}

	s = UniCopyStr(str);

	UniTrim(s);
	if (UniStrLen(s) == 0)
	{
		ret = true;
	}
	else
	{
		ret = false;
	}

	Free(s);

	return ret;
}