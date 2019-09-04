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
 int DumpBufW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ReadDumpExW (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SeekBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool FileCopyExW(wchar_t *src, wchar_t *dst, bool read_lock)
{
	BUF *b;
	bool ret = false;
	// Validate arguments
	if (src == NULL || dst == NULL)
	{
		return false;
	}

	b = ReadDumpExW(src, false);
	if (b == NULL)
	{
		return false;
	}

	SeekBuf(b, 0, 0);

	ret = DumpBufW(b, dst);

	FreeBuf(b);

	return ret;
}