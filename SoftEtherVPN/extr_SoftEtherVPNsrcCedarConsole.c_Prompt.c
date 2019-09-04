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
typedef  char wchar_t ;

/* Variables and functions */
 char* CopyStrToUni (char*) ; 
 char* CopyUniToStr (char*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int IsEmptyStr (char*) ; 
 int /*<<< orphan*/  Print (char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 
 int /*<<< orphan*/  TrimCrlf (char*) ; 
 int /*<<< orphan*/  add_history (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* readline (char*) ; 

wchar_t *Prompt(wchar_t *prompt_str)
{
	wchar_t *ret = NULL;
	wchar_t *tmp = NULL;
	// Validate arguments
	if (prompt_str == NULL)
	{
		prompt_str = L"";
	}

#ifdef	OS_WIN32
	UniPrint(L"%s", prompt_str);
	tmp = Malloc(MAX_PROMPT_STRSIZE);
	if (fgetws(tmp, MAX_PROMPT_STRSIZE - 1, stdin) != NULL)
	{
		bool escape = false;
		UINT i, len;

		len = UniStrLen(tmp);
		for (i = 0;i < len;i++)
		{
			if (tmp[i] == 0x04 || tmp[i] == 0x1A)
			{
				escape = true;
				break;
			}
		}

		if (escape == false)
		{
			UniTrimCrlf(tmp);

			ret = UniCopyStr(tmp);
		}
	}
	Free(tmp);
#else	// OS_WIN32
	{
		char *prompt = CopyUniToStr(prompt_str);
		char *s = readline(prompt);
		Free(prompt);

		if (s != NULL)
		{
			TrimCrlf(s);
			Trim(s);

			if (IsEmptyStr(s) == false)
			{
				add_history(s);
			}

			ret = CopyStrToUni(s);

			free(s);
		}
	}
#endif	// OS_WIN32

	if (ret == NULL)
	{
		Print("\n");
	}

	return ret;
}