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
typedef  int /*<<< orphan*/  fullpath_w ;
typedef  int /*<<< orphan*/  dst_w ;
typedef  int /*<<< orphan*/  basepath_w ;
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int GetRelativePathW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  UniToStr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool GetRelativePath(char *dst, UINT size, char *fullpath, char *basepath)
{
	wchar_t dst_w[MAX_SIZE];
	wchar_t fullpath_w[MAX_SIZE];
	wchar_t basepath_w[MAX_SIZE];
	bool ret;
	// Validate arguments
	if (dst == NULL || fullpath == NULL || basepath == NULL)
	{
		return false;
	}

	StrToUni(fullpath_w, sizeof(fullpath_w), fullpath);
	StrToUni(basepath_w, sizeof(basepath_w), basepath);

	ret = GetRelativePathW(dst_w, sizeof(dst_w), fullpath_w, basepath_w);
	if (ret == false)
	{
		return false;
	}

	UniToStr(dst, size, dst_w);

	return true;
}