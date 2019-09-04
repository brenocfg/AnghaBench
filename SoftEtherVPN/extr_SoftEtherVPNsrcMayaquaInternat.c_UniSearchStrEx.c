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
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int INFINITE ; 
 int /*<<< orphan*/ * Malloc (int) ; 
 scalar_t__ UniStrCmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ UniStrCmpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int UniStrLen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniStrUpper (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcsncmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

UINT UniSearchStrEx(wchar_t *string, wchar_t *keyword, UINT start, bool case_sensitive)
{
	UINT len_string, len_keyword;
	UINT i;
	wchar_t *cmp_string, *cmp_keyword;
	bool found;
	// Validate arguments
	if (string == NULL || keyword == NULL)
	{
		return INFINITE;
	}

	// Get the length of string
	len_string = UniStrLen(string);
	if (len_string <= start)
	{
		// Value of start is invalid
		return INFINITE;
	}

	// Get the length of the keyword
	len_keyword = UniStrLen(keyword);
	if (len_keyword == 0)
	{
		// There is no keyword
		return INFINITE;
	}

	if (len_string < len_keyword)
	{
		return INFINITE;
	}

	if (len_string == len_keyword)
	{
		if (case_sensitive)
		{
			if (UniStrCmp(string, keyword) == 0)
			{
				return 0;
			}
			else
			{
				return INFINITE;
			}
		}
		else
		{
			if (UniStrCmpi(string, keyword) == 0)
			{
				return 0;
			}
			else
			{
				return INFINITE;
			}
		}
	}

	if (case_sensitive)
	{
		cmp_string = string;
		cmp_keyword = keyword;
	}
	else
	{
		cmp_string = Malloc((len_string + 1) * sizeof(wchar_t));
		UniStrCpy(cmp_string, (len_string + 1) * sizeof(wchar_t), string);
		cmp_keyword = Malloc((len_keyword + 1) * sizeof(wchar_t));
		UniStrCpy(cmp_keyword, (len_keyword + 1) * sizeof(wchar_t), keyword);
		UniStrUpper(cmp_string);
		UniStrUpper(cmp_keyword);
	}

	// Search
	found = false;
	for (i = start;i < (len_string - len_keyword + 1);i++)
	{
		// Compare
		if (!wcsncmp(&cmp_string[i], cmp_keyword, len_keyword))
		{
			// Found
			found = true;
			break;
		}
	}

	if (case_sensitive == false)
	{
		// Memory release
		Free(cmp_keyword);
		Free(cmp_string);
	}

	if (found == false)
	{
		return INFINITE;
	}
	return i;
}