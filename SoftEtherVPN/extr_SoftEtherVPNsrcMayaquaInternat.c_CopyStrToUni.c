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
typedef  scalar_t__ UINT ;

/* Variables and functions */
 scalar_t__ CalcStrToUni (char*) ; 
 int /*<<< orphan*/ * CopyUniStr (char*) ; 
 int /*<<< orphan*/ * Malloc (scalar_t__) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,scalar_t__,char*) ; 

wchar_t *CopyStrToUni(char *str)
{
	wchar_t *uni;
	UINT uni_size;
	// Validate arguments
	if (str == NULL)
	{
		return NULL;
	}

	uni_size = CalcStrToUni(str);
	if (uni_size == 0)
	{
		return CopyUniStr(L"");
	}
	uni = Malloc(uni_size);
	StrToUni(uni, uni_size, str);

	return uni;
}