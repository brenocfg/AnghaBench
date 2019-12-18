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
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,char*) ; 
 char* CopyUniStr (char*) ; 
 int /*<<< orphan*/  GetDirNameFromFilePathW (char*,int,char*) ; 
 char* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int MakeDirW (char*) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniFreeStrList (int /*<<< orphan*/ *) ; 
 scalar_t__ UniStrCmpi (char*,char*) ; 
 int /*<<< orphan*/  UniStrCpy (char*,int,char*) ; 

bool MakeDirExW(wchar_t *name)
{
	LIST *o;
	wchar_t tmp[MAX_PATH];
	wchar_t tmp2[MAX_PATH];
	UINT i;
	bool ret = false;
	// Validate arguments
	if (name == NULL)
	{
		return false;
	}

	o = NewListFast(NULL);

	UniStrCpy(tmp, sizeof(tmp), name);
	while (true)
	{
		wchar_t *s = CopyUniStr(tmp);

		Add(o, s);

		GetDirNameFromFilePathW(tmp2, sizeof(tmp2), tmp);

		if (UniStrCmpi(tmp2, tmp) == 0)
		{
			break;
		}

		UniStrCpy(tmp, sizeof(tmp), tmp2);
	}

	for (i = 0;i < LIST_NUM(o);i++)
	{
		UINT j = LIST_NUM(o) - i - 1;
		wchar_t *s = LIST_DATA(o, j);

		if (UniStrCmpi(s, L"\\") != 0 && UniStrCmpi(s, L"/") != 0)
		{
			ret = MakeDirW(s);
		}
	}

	UniFreeStrList(o);

	return ret;
}