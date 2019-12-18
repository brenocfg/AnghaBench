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
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_4__ {int NumTokens; char** Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;

/* Variables and functions */
 int /*<<< orphan*/  DebugPrintAllObjects () ; 
 int /*<<< orphan*/  DebugPrintCommandList () ; 
 int /*<<< orphan*/  DebugPrintObjectInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 int /*<<< orphan*/  GetLine (char*,int) ; 
 int MAX_SIZE ; 
 TYPE_1__* ParseToken (char*,char*) ; 
 int /*<<< orphan*/  Print (char*) ; 
 int /*<<< orphan*/  StrCmpi (char*,char*) ; 
 int /*<<< orphan*/  ToInt (char*) ; 
 int g_memcheck ; 

void MemoryDebugMenu()
{
	char tmp[MAX_SIZE];
	TOKEN_LIST *t;
	char *cmd;
	Print("Mayaqua Kernel Memory Debug Tools\n"
		"Copyright (c) SoftEther VPN Project. All Rights Reserved.\n\n");

#ifndef	OS_WIN32
	Print("Unfortunately The call stack is not recorded on non-Windows systems\n");
	Print("since UnixGetCallStack() and UnixGetCallStackSymbolInfo() is not implemented.\n");
	Print("Therefore please use valgrind or other memory leak check tools\n");
	Print("to get the actual call stacks of memory leak causes.\n\n");
#endif	// OS_WIN32

	g_memcheck = false;
	while (true)
	{
		Print("debug>");
		GetLine(tmp, sizeof(tmp));
		t = ParseToken(tmp, " \t");
		if (t->NumTokens == 0)
		{
			FreeToken(t);
			DebugPrintAllObjects();
			continue;
		}
		cmd = t->Token[0];
		if (!StrCmpi(cmd, "?"))
		{
			DebugPrintCommandList();
		}
		else if (!StrCmpi(cmd, "a"))
		{
			DebugPrintAllObjects();
		}
		else if (!StrCmpi(cmd, "i"))
		{
			if (t->NumTokens == 1)
			{
				Print("Usage: i <obj_id>\n\n");
			}
			else
			{
				DebugPrintObjectInfo(ToInt(t->Token[1]));
			}
		}
		else if (!StrCmpi(cmd, "q"))
		{
			break;
		}
		else if (ToInt(cmd) != 0)
		{
			DebugPrintObjectInfo(ToInt(t->Token[0]));
		}
		else
		{
			Print("Command Not Found,\n\n");
		}
		FreeToken(t);
	}
	FreeToken(t);
	g_memcheck = true;
}