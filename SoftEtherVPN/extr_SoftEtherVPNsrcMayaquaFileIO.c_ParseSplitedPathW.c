#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
struct TYPE_4__ {size_t NumTokens; char** Token; } ;
typedef  TYPE_1__ UNI_TOKEN_LIST ;
typedef  size_t UINT ;

/* Variables and functions */
 int /*<<< orphan*/  Free (char*) ; 
 char* UniCopyStr (char*) ; 
 TYPE_1__* UniParseToken (char*,char*) ; 
 int /*<<< orphan*/  UniTrim (char*) ; 
 int /*<<< orphan*/  UniTrimCrlf (char*) ; 

UNI_TOKEN_LIST *ParseSplitedPathW(wchar_t *path)
{
	UNI_TOKEN_LIST *ret;
	wchar_t *tmp = UniCopyStr(path);
	wchar_t *split_str;
	UINT i;

	UniTrim(tmp);
	UniTrimCrlf(tmp);
	UniTrim(tmp);
	UniTrimCrlf(tmp);

#ifdef	OS_WIN32
	split_str = L";";
#else	// OS_WIN32
	split_str = L":";
#endif	// OS_WIN32

	ret = UniParseToken(tmp, split_str);

	if (ret != NULL)
	{
		for (i = 0;i < ret->NumTokens;i++)
		{
			UniTrim(ret->Token[i]);
			UniTrimCrlf(ret->Token[i]);
			UniTrim(ret->Token[i]);
			UniTrimCrlf(ret->Token[i]);
		}
	}

	Free(tmp);

	return ret;
}