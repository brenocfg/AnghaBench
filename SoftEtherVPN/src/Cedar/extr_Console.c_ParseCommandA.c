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
 int /*<<< orphan*/ * CopyStrToUni (char*) ; 
 char* CopyUniToStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ParseCommand (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

char *ParseCommandA(wchar_t *str, char *name)
{
	wchar_t *tmp1, *tmp2;
	char *ret;
	// Validate arguments
	if (str == NULL)
	{
		return NULL;
	}

	if (name != NULL)
	{
		tmp1 = CopyStrToUni(name);
	}
	else
	{
		tmp1 = NULL;
	}

	tmp2 = ParseCommand(str, tmp1);

	if (tmp2 == NULL)
	{
		ret = NULL;
	}
	else
	{
		ret = CopyUniToStr(tmp2);
		Free(tmp2);
	}

	Free(tmp1);

	return ret;
}