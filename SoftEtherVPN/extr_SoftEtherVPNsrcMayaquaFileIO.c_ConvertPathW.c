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
typedef  int wchar_t ;
typedef  size_t UINT ;

/* Variables and functions */
 size_t UniStrLen (int*) ; 

void ConvertPathW(wchar_t *path)
{
	UINT i, len;
#ifdef	PATH_BACKSLASH
	wchar_t new_char = L'\\';
#else
	wchar_t new_char = L'/';
#endif

	len = UniStrLen(path);
	for (i = 0;i < len;i++)
	{
		if (path[i] == L'\\' || path[i] == L'/')
		{
			path[i] = new_char;
		}
	}
}