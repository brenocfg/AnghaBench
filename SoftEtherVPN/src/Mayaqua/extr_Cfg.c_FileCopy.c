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
 int DumpBuf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ReadDump (char*) ; 
 int /*<<< orphan*/  SeekBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool FileCopy(char *src, char *dst)
{
	BUF *b;
	bool ret = false;
	// Validate arguments
	if (src == NULL || dst == NULL)
	{
		return false;
	}

	b = ReadDump(src);
	if (b == NULL)
	{
		return false;
	}

	SeekBuf(b, 0, 0);

	ret = DumpBuf(b, dst);

	FreeBuf(b);

	return ret;
}