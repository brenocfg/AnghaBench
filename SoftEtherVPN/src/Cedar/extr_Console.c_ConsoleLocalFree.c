#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ Win32_OldConsoleWidth; int /*<<< orphan*/  OutputLock; int /*<<< orphan*/ * OutFile; int /*<<< orphan*/  InBuf; int /*<<< orphan*/ * InFile; scalar_t__ Param; } ;
typedef  TYPE_1__ LOCAL_CONSOLE_PARAM ;
typedef  TYPE_1__ CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FileClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MsSetConsoleWidth (scalar_t__) ; 

void ConsoleLocalFree(CONSOLE *c)
{
	LOCAL_CONSOLE_PARAM *p;
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	p = (LOCAL_CONSOLE_PARAM *)c->Param;

#ifdef	OS_WIN32
	if (p->Win32_OldConsoleWidth != 0)
	{
		MsSetConsoleWidth(p->Win32_OldConsoleWidth);
	}
#endif	// OS_WIN32

	if (p != NULL)
	{
		if (p->InFile != NULL)
		{
			FileClose(p->InFile);
			FreeBuf(p->InBuf);
		}

		if (p->OutFile != NULL)
		{
			FileClose(p->OutFile);
		}

		Free(p);
	}

	DeleteLock(c->OutputLock);

	// Memory release
	Free(c);
}