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
typedef  int UINT ;

/* Variables and functions */
 int CalcStrToUni (char*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 char* Malloc (int) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 int UniStrCpy (char*,int,char*) ; 
 int UnixStrToUni (char*,int,char*) ; 
 int /*<<< orphan*/  mbstowcs (char*,char*,int /*<<< orphan*/ ) ; 

UINT StrToUni(wchar_t *s, UINT size, char *str)
{
#ifdef	OS_WIN32
	UINT ret;
	wchar_t *tmp;
	UINT new_size;
	// Validate arguments
	if (s == NULL || str == NULL)
	{
		return 0;
	}

	new_size = CalcStrToUni(str);
	if (new_size == 0)
	{
		if (size >= 2)
		{
			UniStrCpy(s, 0, L"");
		}
		return 0;
	}
	tmp = Malloc(new_size);
	tmp[0] = 0;
	mbstowcs(tmp, str, StrLen(str));
	tmp[(new_size - 1) / sizeof(wchar_t)] = 0;
	ret = UniStrCpy(s, size, tmp);
	Free(tmp);

	return ret;
#else	// OS_WIN32
	return UnixStrToUni(s, size, str);
#endif	// OS_WIN32
}