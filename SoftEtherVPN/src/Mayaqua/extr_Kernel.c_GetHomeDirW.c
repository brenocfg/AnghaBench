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
typedef  int /*<<< orphan*/  hpath ;
typedef  int /*<<< orphan*/  drive ;
typedef  int UINT ;

/* Variables and functions */
 int GetEnvW (char*,int /*<<< orphan*/ *,int) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnixGetCurrentDirW (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Win32GetCurrentDirW (int /*<<< orphan*/ *,int) ; 

void GetHomeDirW(wchar_t *path, UINT size)
{
	// Validate arguments
	if (path == NULL)
	{
		return;
	}

	if (GetEnvW(L"HOME", path, size) == false)
	{
		wchar_t drive[MAX_SIZE];
		wchar_t hpath[MAX_SIZE];
		if (GetEnvW(L"HOMEDRIVE", drive, sizeof(drive)) &&
			GetEnvW(L"HOMEPATH", hpath, sizeof(hpath)))
		{
			UniFormat(path, size, L"%s%s", drive, hpath);
		}
		else
		{
#ifdef	OS_WIN32
			Win32GetCurrentDirW(path, size);
#else	// OS_WIN32
			UnixGetCurrentDirW(path, size);
#endif	// OS_WIN32
		}
	}
}