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
typedef  int /*<<< orphan*/  FOLDER ;
typedef  int /*<<< orphan*/  CFG_RW ;

/* Variables and functions */
 int CfgSaveExW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CopyStrToUni (char*) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 

bool CfgSaveEx(CFG_RW *rw, FOLDER *f, char *name)
{
	wchar_t *name_w = CopyStrToUni(name);
	bool ret = CfgSaveExW(rw, f, name_w);

	Free(name_w);

	return ret;
}