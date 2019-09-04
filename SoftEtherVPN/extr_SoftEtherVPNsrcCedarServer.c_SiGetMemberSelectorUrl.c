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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 char* CfgReadNextLine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int IsEmptyStr (char*) ; 
 int /*<<< orphan*/  MEMBER_SELECTOR_TXT_FILENAME ; 
 int /*<<< orphan*/ * ReadDump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 

bool SiGetMemberSelectorUrl(char *url, UINT url_size)
{
	BUF *b;
	bool ret = false;
	// Validate arguments
	if (url == NULL)
	{
		return false;
	}

	b = ReadDump(MEMBER_SELECTOR_TXT_FILENAME);
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

		if (IsEmptyStr(line) == false && ret == false)
		{
			StrCpy(url, url_size, line);
			ret = true;
		}

		Free(line);
	}

	FreeBuf(b);

	return ret;
}