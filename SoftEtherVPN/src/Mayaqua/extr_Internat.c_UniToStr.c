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
 int CalcUniToStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (char*) ; 
 char* Malloc (int) ; 
 int StrCpy (char*,int,char*) ; 
 int UnixUniToStr (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcstombs (char*,int /*<<< orphan*/ *,int) ; 

UINT UniToStr(char *str, UINT size, wchar_t *s)
{
#ifdef	OS_WIN32
	UINT ret;
	char *tmp;
	UINT new_size;
	// Validate arguments
	if (s == NULL || str == NULL)
	{
		return 0;
	}

	new_size = CalcUniToStr(s);
	if (new_size == 0)
	{
		if (size >= 1)
		{
			StrCpy(str, 0, "");
		}
		return 0;
	}
	tmp = Malloc(new_size);
	tmp[0] = 0;
	wcstombs(tmp, s, new_size);
	tmp[new_size - 1] = 0;
	ret = StrCpy(str, size, tmp);
	Free(tmp);

	return ret;
#else	// OS_WIN32
	return UnixUniToStr(str, size, s);
#endif	// OS_WIN32
}