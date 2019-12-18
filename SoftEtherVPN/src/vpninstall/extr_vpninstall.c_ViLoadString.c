#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int UINT ;
struct TYPE_2__ {int /*<<< orphan*/  OsType; } ;
typedef  int /*<<< orphan*/  HINSTANCE ;

/* Variables and functions */
 char* CopyStrToUni (char*) ; 
 char* CopyUniStr (char*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 TYPE_1__* GetOsInfo () ; 
 scalar_t__ LoadStringW (int /*<<< orphan*/ ,int,char*,int) ; 
 char* Malloc (int) ; 
 scalar_t__ OS_IS_WINDOWS_9X (int /*<<< orphan*/ ) ; 
 char* ViLoadStringA (int /*<<< orphan*/ ,int) ; 

wchar_t *ViLoadString(HINSTANCE hInst, UINT id)
{
	wchar_t *ret = NULL;

	if (OS_IS_WINDOWS_9X(GetOsInfo()->OsType))
	{
		char *a = ViLoadStringA(hInst, id);
		if (a != NULL)
		{
			ret = CopyStrToUni(a);
			Free(a);
		}
	}
	else
	{
		UINT tmp_size = 60000;
		wchar_t *tmp = Malloc(tmp_size);

		if (LoadStringW(hInst, id, tmp, tmp_size) != 0)
		{
			ret = CopyUniStr(tmp);
		}

		Free(tmp);
	}

	return ret;
}