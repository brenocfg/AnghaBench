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
typedef  int UINT ;

/* Variables and functions */
 int /*<<< orphan*/ * CopyUniStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int UniStrCmpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniTrim (int /*<<< orphan*/ *) ; 

int UniSoftStrCmp(wchar_t *str1, wchar_t *str2)
{
	UINT ret;
	wchar_t *tmp1, *tmp2;
	// Validate arguments
	if (str1 == NULL && str2 == NULL)
	{
		return 0;
	}
	if (str1 == NULL)
	{
		return 1;
	}
	if (str2 == NULL)
	{
		return -1;
	}

	tmp1 = CopyUniStr(str1);
	tmp2 = CopyUniStr(str2);

	UniTrim(tmp1);
	UniTrim(tmp2);

	ret = UniStrCmpi(tmp1, tmp2);

	Free(tmp1);
	Free(tmp2);

	return ret;
}