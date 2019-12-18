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
 int CiTryToParseAccount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ReadDumpW (int /*<<< orphan*/ *) ; 

bool CiTryToParseAccountFile(wchar_t *name)
{
	bool ret;
	BUF *b;
	// Validate arguments
	if (name == NULL)
	{
		return false;
	}

	b = ReadDumpW(name);
	if (b == NULL)
	{
		return false;
	}

	ret = CiTryToParseAccount(b);

	FreeBuf(b);

	return ret;
}