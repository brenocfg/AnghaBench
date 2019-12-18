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
 int /*<<< orphan*/  Free (scalar_t__*) ; 
 int INFINITE ; 
 scalar_t__* Malloc (int) ; 
 int UniCalcReplaceStrEx (scalar_t__*,scalar_t__*,scalar_t__*,int) ; 
 int UniSearchStrEx (scalar_t__*,scalar_t__*,int,int) ; 
 int /*<<< orphan*/  UniStrCpy (scalar_t__*,int,scalar_t__*) ; 
 int UniStrLen (scalar_t__*) ; 

UINT UniReplaceStrEx(wchar_t *dst, UINT size, wchar_t *string, wchar_t *old_keyword, wchar_t *new_keyword, bool case_sensitive)
{
	UINT i, j, num, len_string, len_old, len_new, len_ret, wp;
	wchar_t *ret;
	// Validate arguments
	if (string == NULL || old_keyword == NULL || new_keyword == NULL)
	{
		return 0;
	}

	// Get the length of the string
	len_string = UniStrLen(string);
	len_old = UniStrLen(old_keyword);
	len_new = UniStrLen(new_keyword);

	// Get the final string length
	len_ret = UniCalcReplaceStrEx(string, old_keyword, new_keyword, case_sensitive);
	// Memory allocation
	ret = Malloc((len_ret + 1) * sizeof(wchar_t));
	ret[len_ret] = 0;

	// Search and Replace
	i = j = num = wp = 0;
	while (true)
	{
		i = UniSearchStrEx(string, old_keyword, i, case_sensitive);
		if (i == INFINITE)
		{
			Copy(&ret[wp], &string[j], (len_string - j) * sizeof(wchar_t));
			wp += len_string - j;
			break;
		}
		num++;
		Copy(&ret[wp], &string[j], (i - j) * sizeof(wchar_t));
		wp += i - j;
		Copy(&ret[wp], new_keyword, len_new * sizeof(wchar_t));
		wp += len_new;
		i += len_old;
		j = i;
	}

	// Copy of the search results
	UniStrCpy(dst, size, ret);

	// Memory release
	Free(ret);

	return num;
}