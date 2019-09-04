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
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int IsInLines (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * ReadDumpW (int /*<<< orphan*/ *) ; 

bool IsInLinesFile(wchar_t *filename, char *str, bool instr)
{
	bool ret = false;
	BUF *b;
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

	ret = IsInLines(b, str, instr);

	FreeBuf(b);

	return ret;
}