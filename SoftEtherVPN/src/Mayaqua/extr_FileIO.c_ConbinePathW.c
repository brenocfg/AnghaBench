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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  filename_ident ;
typedef  int UINT ;

/* Variables and functions */
 int MAX_SIZE ; 
 int /*<<< orphan*/  NormalizePathW (int*,int,int*) ; 
 int UniEndWith (int*,char*) ; 
 scalar_t__ UniStartWith (int*,char*) ; 
 int /*<<< orphan*/  UniStrCat (int*,int,...) ; 
 int /*<<< orphan*/  UniStrCpy (int*,int,int*) ; 
 int UniStrLen (int*) ; 

void ConbinePathW(wchar_t *dst, UINT size, wchar_t *dirname, wchar_t *filename)
{
	bool is_full_path;
	wchar_t tmp[MAX_SIZE];
	wchar_t filename_ident[MAX_SIZE];
	// Validate arguments
	if (dst == NULL || dirname == NULL || filename == NULL)
	{
		return;
	}

	NormalizePathW(filename_ident, sizeof(filename_ident), filename);

	is_full_path = false;

	if (UniStartWith(filename_ident, L"\\") || UniStartWith(filename_ident, L"/"))
	{
		is_full_path = true;
	}

	filename = &filename_ident[0];

#ifdef	OS_WIN32
	if (UniStrLen(filename) >= 2)
	{
		if ((L'a' <= filename[0] && filename[0] <= L'z') || (L'A' <= filename[0] && filename[0] <= L'Z'))
		{
			if (filename[1] == L':')
			{
				is_full_path = true;
			}
		}
	}
#endif	// OS_WIN32

	if (is_full_path == false)
	{
		UniStrCpy(tmp, sizeof(tmp), dirname);
		if (UniEndWith(tmp, L"/") == false && UniEndWith(tmp, L"\\") == false)
		{
			UniStrCat(tmp, sizeof(tmp), L"/");
		}
		UniStrCat(tmp, sizeof(tmp), filename);
	}
	else
	{
		UniStrCpy(tmp, sizeof(tmp), filename);
	}

	NormalizePathW(dst, size, tmp);
}