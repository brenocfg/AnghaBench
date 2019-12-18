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
typedef  int /*<<< orphan*/  DIRLIST ;
typedef  int /*<<< orphan*/  COMPARE ;

/* Variables and functions */
 int /*<<< orphan*/ * CopyStrToUni (char*) ; 
 int /*<<< orphan*/ * EnumDirExW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 

DIRLIST *EnumDirEx(char *dirname, COMPARE *compare)
{
	wchar_t *dirname_w = CopyStrToUni(dirname);
	DIRLIST *ret = EnumDirExW(dirname_w, compare);

	Free(dirname_w);

	return ret;
}