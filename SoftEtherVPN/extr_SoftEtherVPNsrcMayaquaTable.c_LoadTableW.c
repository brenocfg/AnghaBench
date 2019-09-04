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
typedef  int /*<<< orphan*/  replace_name ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 char* CfgReadNextLine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int IsEmptyStr (char*) ; 
 int LoadTableMain (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/ * ReadDump (char*) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

bool LoadTableW(wchar_t *filename)
{
	bool ret;
	BUF *b;
	wchar_t replace_name[MAX_PATH];

	Zero(replace_name, sizeof(replace_name));

	b = ReadDump("@table_name.txt");
	if (b != NULL)
	{
		char *s = CfgReadNextLine(b);
		if (s != NULL)
		{
			if (IsEmptyStr(s) == false)
			{
				StrToUni(replace_name, sizeof(replace_name), s);
				filename = replace_name;
			}

			Free(s);
		}
		FreeBuf(b);
	}

	ret = LoadTableMain(filename);

	return ret;
}