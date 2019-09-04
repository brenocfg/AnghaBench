#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  ZIP_PACKER ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 scalar_t__ IsEmptyStr (char*) ; 
 TYPE_1__* ReadDumpW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZipAddFileSimple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool ZipAddRealFileW(ZIP_PACKER *p, char *name, UINT64 dt, UINT attribute, wchar_t *srcname)
{
	BUF *b;
	// Validate arguments
	if (p == NULL || IsEmptyStr(name) || srcname == NULL)
	{
		return false;
	}

	b = ReadDumpW(srcname);
	if (b == NULL)
	{
		return false;
	}

	ZipAddFileSimple(p, name, dt, attribute, b->Buf, b->Size);

	FreeBuf(b);

	return true;
}