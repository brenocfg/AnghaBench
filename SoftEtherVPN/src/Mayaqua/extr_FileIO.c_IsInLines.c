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
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 char* CfgReadNextLine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (char*) ; 
 scalar_t__ InStr (char*,char*) ; 
 int IsEmptyStr (char*) ; 
 int /*<<< orphan*/  SeekBufToBegin (int /*<<< orphan*/ *) ; 
 scalar_t__ StrCmpi (char*,char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 

bool IsInLines(BUF *buf, char *str, bool instr)
{
	bool ret = false;
	// Validate arguments
	if (buf == NULL || str == NULL)
	{
		return false;
	}

	if (IsEmptyStr(str))
	{
		return false;
	}

	SeekBufToBegin(buf);

	while (ret == false)
	{
		char *line = CfgReadNextLine(buf);

		if (line == NULL)
		{
			break;
		}

		Trim(line);

		if (IsEmptyStr(line) == false)
		{
			if (StrCmpi(line, str) == 0)
			{
				ret = true;
			}

			if (instr)
			{
				if (InStr(str, line))
				{
					ret = true;
				}

				if (InStr(line, str))
				{
					ret = true;
				}
			}
		}

		Free(line);
	}

	return ret;
}