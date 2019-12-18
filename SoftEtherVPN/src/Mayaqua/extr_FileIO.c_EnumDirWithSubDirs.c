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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  UNI_TOKEN_LIST ;
typedef  int /*<<< orphan*/  TOKEN_LIST ;

/* Variables and functions */
 int /*<<< orphan*/ * EnumDirWithSubDirsW (int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  UniFreeToken (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * UniTokenListToTokenList (int /*<<< orphan*/ *) ; 

TOKEN_LIST *EnumDirWithSubDirs(char *dirname)
{
	TOKEN_LIST *ret;
	UNI_TOKEN_LIST *ret2;
	wchar_t tmp[MAX_SIZE];
	// Validate arguments
	if (dirname == NULL)
	{
		dirname = "./";
	}

	StrToUni(tmp, sizeof(tmp), dirname);

	ret2 = EnumDirWithSubDirsW(tmp);

	ret = UniTokenListToTokenList(ret2);

	UniFreeToken(ret2);

	return ret;
}