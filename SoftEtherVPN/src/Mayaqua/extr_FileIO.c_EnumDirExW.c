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
typedef  int /*<<< orphan*/  DIRLIST ;
typedef  int /*<<< orphan*/  COMPARE ;

/* Variables and functions */
 int /*<<< orphan*/ * CompareDirListByName ; 
 int /*<<< orphan*/ * UnixEnumDirExW (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Win32EnumDirExW (char*,int /*<<< orphan*/ *) ; 

DIRLIST *EnumDirExW(wchar_t *dirname, COMPARE *compare)
{
	DIRLIST *d = NULL;
	// Validate arguments
	if (dirname == NULL)
	{
		dirname = L"./";
	}

	if (compare == NULL)
	{
		compare = CompareDirListByName;
	}

#ifdef	OS_WIN32
	d = Win32EnumDirExW(dirname, compare);
#else	// OS_WIN32
	d = UnixEnumDirExW(dirname, compare);
#endif	// OS_WIN32

	return d;
}