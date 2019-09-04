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
typedef  int /*<<< orphan*/  ZIP_PACKER ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int /*<<< orphan*/ * CopyStrToUni (char*) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int ZipAddRealFileW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool ZipAddRealFile(ZIP_PACKER *p, char *name, UINT64 dt, UINT attribute, char *srcname)
{
	bool ret = false;
	wchar_t *s;

	s = CopyStrToUni(srcname);

	ret = ZipAddRealFileW(p, name, dt, attribute, s);

	Free(s);

	return ret;
}