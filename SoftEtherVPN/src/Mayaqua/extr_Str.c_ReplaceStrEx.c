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
typedef  int UINT ;

/* Variables and functions */
 int CalcReplaceStrEx (char*,char*,char*,int) ; 
 int /*<<< orphan*/  Copy (char*,char*,int) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int INFINITE ; 
 char* Malloc (int) ; 
 int SearchStrEx (char*,char*,int,int) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int StrLen (char*) ; 

UINT ReplaceStrEx(char *dst, UINT size, char *string, char *old_keyword, char *new_keyword, bool case_sensitive)
{
	UINT i, j, num;
	UINT len_string, len_old, len_new;
	UINT len_ret;
	UINT wp;
	char *ret;
	// Validate arguments
	if (string == NULL || old_keyword == NULL || new_keyword == NULL)
	{
		return 0;
	}

	// Get the length of the string
	len_string = StrLen(string);
	len_old = StrLen(old_keyword);
	len_new = StrLen(new_keyword);

	// Calculate the final string length
	len_ret = CalcReplaceStrEx(string, old_keyword, new_keyword, case_sensitive);
	// Memory allocation
	ret = Malloc(len_ret + 1);
	ret[len_ret] = '\0';

	// Search and Replace
	i = 0;
	j = 0;
	num = 0;
	wp = 0;
	while (true)
	{
		i = SearchStrEx(string, old_keyword, i, case_sensitive);
		if (i == INFINITE)
		{
			Copy(ret + wp, string + j, len_string - j);
			wp += len_string - j;
			break;
		}
		num++;
		Copy(ret + wp, string + j, i - j);
		wp += i - j;
		Copy(ret + wp, new_keyword, len_new);
		wp += len_new;
		i += len_old;
		j = i;
	}

	// Copy of the search results
	StrCpy(dst, size, ret);

	// Memory release
	Free(ret);

	return num;
}