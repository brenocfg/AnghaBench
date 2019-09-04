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
typedef  scalar_t__ UINT ;

/* Variables and functions */
 int /*<<< orphan*/  Free (char*) ; 
 scalar_t__ INFINITE ; 
 char* Malloc (scalar_t__) ; 
 int /*<<< orphan*/  StrCpy (char*,scalar_t__,char*) ; 
 scalar_t__ StrLen (char*) ; 
 int /*<<< orphan*/  StrUpper (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,scalar_t__) ; 

UINT SearchStrEx(char *string, char *keyword, UINT start, bool case_sensitive)
{
	UINT len_string, len_keyword;
	UINT i;
	char *cmp_string, *cmp_keyword;
	bool found;
	// Validate arguments
	if (string == NULL || keyword == NULL)
	{
		return INFINITE;
	}

	// Get the length of string
	len_string = StrLen(string);
	if (len_string <= start)
	{
		// Value of start is invalid
		return INFINITE;
	}

	// Get the length of the keyword
	len_keyword = StrLen(keyword);
	if (len_keyword == 0)
	{
		// There is no keyword in the string
		return INFINITE;
	}

	if ((len_string - start) < len_keyword)
	{
		// The keyword is longer than the string
		return INFINITE;
	}

	if (case_sensitive)
	{
		cmp_string = string;
		cmp_keyword = keyword;
	}
	else
	{
		cmp_string = Malloc(len_string + 1);
		StrCpy(cmp_string, len_string + 1, string);
		cmp_keyword = Malloc(len_keyword + 1);
		StrCpy(cmp_keyword, len_keyword + 1, keyword);
		StrUpper(cmp_string);
		StrUpper(cmp_keyword);
	}

	// Search
	found = false;
	for (i = start;i < (len_string - len_keyword + 1);i++)
	{
		// Compare
		if (!strncmp(&cmp_string[i], cmp_keyword, len_keyword))
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