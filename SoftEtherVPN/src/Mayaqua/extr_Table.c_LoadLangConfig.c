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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 char* CfgReadNextLine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int InStr (char*,char*) ; 
 int IsEmptyStr (char*) ; 
 int /*<<< orphan*/ * ReadDumpW (int /*<<< orphan*/ *) ; 
 int StartWith (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 

bool LoadLangConfig(wchar_t *filename, char *str, UINT str_size)
{
	BUF *b;
	bool ret = false;
	// Validate arguments
	if (filename == NULL || str == NULL)
	{
		return false;
	}

	b = ReadDumpW(filename);
	if (b == NULL)
	{
		return false;
	}

	while (true)
	{
		char *line = CfgReadNextLine(b);

		if (line == NULL)
		{
			break;
		}

		Trim(line);

		if (IsEmptyStr(line) == false)
		{
			if (StartWith(line, "#") == false && StartWith(line, "//") == false && StartWith(line, ";") == false &&
				InStr(line, "#") == false)
			{
				StrCpy(str, str_size, line);
				ret = true;
			}
		}

		Free(line);
	}

	FreeBuf(b);

	return ret;
}