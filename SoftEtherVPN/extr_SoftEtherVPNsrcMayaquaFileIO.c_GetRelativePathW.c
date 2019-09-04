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
typedef  int /*<<< orphan*/  fullpath2 ;
typedef  int /*<<< orphan*/  basepath2 ;
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int /*<<< orphan*/  ClearUniStr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  NormalizePathW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int UniStartWith (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniStrCat (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int UniStrLen (int /*<<< orphan*/ *) ; 

bool GetRelativePathW(wchar_t *dst, UINT size, wchar_t *fullpath, wchar_t *basepath)
{
	wchar_t fullpath2[MAX_SIZE];
	wchar_t basepath2[MAX_SIZE];
	// Validate arguments
	if (dst == NULL || fullpath == NULL || basepath == NULL)
	{
		return false;
	}
	ClearUniStr(dst, size);

	NormalizePathW(fullpath2, sizeof(fullpath2), fullpath);
	NormalizePathW(basepath2, sizeof(basepath2), basepath);

#ifdef	OS_WIN32
	UniStrCat(basepath2, sizeof(basepath2), L"\\");
#else	// OS_WIN32
	UniStrCat(basepath2, sizeof(basepath2), L"/");
#endif	// OS_WIN32

	if (UniStrLen(fullpath2) <= UniStrLen(basepath2))
	{
		return false;
	}

	if (UniStartWith(fullpath2, basepath2) == false)
	{
		return false;
	}

	UniStrCpy(dst, size, fullpath2 + UniStrLen(basepath2));

	return true;
}