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
struct TYPE_4__ {int HamMode; int /*<<< orphan*/  HamBuf; int /*<<< orphan*/  pData; int /*<<< orphan*/  SetUpdateTime; int /*<<< orphan*/  SetCreateTime; scalar_t__ WriteMode; } ;
typedef  TYPE_1__ IO ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_IO_CLOSE_COUNT ; 
 int /*<<< orphan*/  OSFileClose (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Win32FileSetDate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void FileCloseEx(IO *o, bool no_flush)
{
	// Validate arguments
	if (o == NULL)
	{
		return;
	}

	if (o->HamMode == false)
	{
		if (o->WriteMode)
		{
#ifdef	OS_WIN32
			Win32FileSetDate(o->pData, o->SetCreateTime, o->SetUpdateTime);
#endif	// OS_WIN32
		}

		OSFileClose(o->pData, no_flush);
	}
	else
	{
		FreeBuf(o->HamBuf);
	}
	Free(o);

	// KS
	KS_INC(KS_IO_CLOSE_COUNT);
}