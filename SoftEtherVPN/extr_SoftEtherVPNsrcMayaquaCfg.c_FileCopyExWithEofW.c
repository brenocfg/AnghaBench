#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_7__ {int /*<<< orphan*/  Size; } ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int DumpBufW (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 TYPE_1__* ReadDumpExW (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SeekBuf (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBufChar (TYPE_1__*,int) ; 

bool FileCopyExWithEofW(wchar_t *src, wchar_t *dst, bool read_lock)
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

	SeekBuf(b, b->Size, 0);

	WriteBufChar(b, 0x1A);

	SeekBuf(b, 0, 0);

	ret = DumpBufW(b, dst);

	FreeBuf(b);

	return ret;
}