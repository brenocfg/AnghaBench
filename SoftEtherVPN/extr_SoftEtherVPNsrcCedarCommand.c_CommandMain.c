#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  cmd ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_8__ {char* member_0; int /*<<< orphan*/  member_1; } ;
struct TYPE_7__ {int ProgrammingMode; int /*<<< orphan*/  (* Free ) (TYPE_1__*) ;int /*<<< orphan*/  RetCode; int /*<<< orphan*/  ConsoleType; } ;
typedef  TYPE_1__ CONSOLE ;
typedef  TYPE_2__ CMD ;

/* Variables and functions */
 int /*<<< orphan*/  CONSOLE_CSV ; 
 char* CopyUniToStr (char*) ; 
 int DispatchNextCmdEx (TYPE_1__*,char*,char*,TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  Free (char*) ; 
 TYPE_1__* NewLocalConsole (char*,char*) ; 
 char* ParseCommand (char*,char*) ; 
 int /*<<< orphan*/  Print (char*) ; 
 scalar_t__ UniIsEmptyStr (char*) ; 
 int /*<<< orphan*/  VpnCmdProc ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

UINT CommandMain(wchar_t *command_line)
{
	UINT ret = 0;
	wchar_t *infile, *outfile;
	char *a_infile, *a_outfile;
	wchar_t *csvmode;
	wchar_t *programming_mode;
	CONSOLE *c;

	// Validate arguments
	if (command_line == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	// Look ahead only items of /in and /out
	infile = ParseCommand(command_line, L"in");
	outfile = ParseCommand(command_line, L"out");
	if (UniIsEmptyStr(infile))
	{
		Free(infile);
		infile = NULL;
	}
	if (UniIsEmptyStr(outfile))
	{
		Free(outfile);
		outfile = NULL;
	}

	a_infile = CopyUniToStr(infile);
	a_outfile = CopyUniToStr(outfile);

	// Allocate the local console
	c = NewLocalConsole(infile, outfile);
	if (c != NULL)
	{
		// Definition of commands of vpncmd
		CMD cmd[] =
		{
			{"vpncmd", VpnCmdProc},
		};

		// Read ahead to check the CSV mode
		csvmode = ParseCommand(command_line, L"csv");
		if(csvmode != NULL)
		{
			Free(csvmode);
			c->ConsoleType = CONSOLE_CSV;
		}

		programming_mode = ParseCommand(command_line, L"programming");
		if (programming_mode != NULL)
		{
			Free(programming_mode);
			c->ProgrammingMode = true;
		}

		if (DispatchNextCmdEx(c, command_line, ">", cmd, sizeof(cmd) / sizeof(cmd[0]), NULL) == false)
		{
			ret = ERR_INVALID_PARAMETER;
		}
		else
		{
			ret = c->RetCode;
		}

		// Release the local console
		c->Free(c);
	}
	else
	{
		Print("Error: Couldn't open local console.\n");
	}

	Free(a_infile);
	Free(a_outfile);
	Free(infile);
	Free(outfile);

	return ret;
}