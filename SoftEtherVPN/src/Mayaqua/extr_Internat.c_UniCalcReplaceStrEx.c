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
 scalar_t__ INFINITE ; 
 scalar_t__ UniSearchStrEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int) ; 
 scalar_t__ UniStrLen (int /*<<< orphan*/ *) ; 

UINT UniCalcReplaceStrEx(wchar_t *string, wchar_t *old_keyword, wchar_t *new_keyword, bool case_sensitive)
{
	UINT i, num;
	UINT len_string, len_old, len_new;
	// Validate arguments
	if (string == NULL || old_keyword == NULL || new_keyword == NULL)
	{
		return 0;
	}

	// Get the length of the string
	len_string = UniStrLen(string);
	len_old = UniStrLen(old_keyword);
	len_new = UniStrLen(new_keyword);

	if (len_old == len_new)
	{
		return len_string;
	}

	// Search process
	num = 0;
	i = 0;
	while (true)
	{
		i = UniSearchStrEx(string, old_keyword, i, case_sensitive);
		if (i == INFINITE)
		{
			break;
		}
		i += len_old;
		num++;
	}

	// Calculation
	return len_string + len_new * num - len_old * num;
}