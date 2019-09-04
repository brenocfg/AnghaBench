#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_23__ {int NumTokens; int /*<<< orphan*/ * Token; } ;
typedef  TYPE_1__ UNI_TOKEN_LIST ;
typedef  int UINT ;
struct TYPE_25__ {int /*<<< orphan*/  (* Write ) (TYPE_3__*,char*) ;} ;
struct TYPE_24__ {int NumTokens; } ;
typedef  TYPE_2__ TOKEN_LIST ;
typedef  TYPE_3__ CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  GetCommandHelpStr (char*,char**,char**,char**) ; 
 int GetConsoleWidth (TYPE_3__*) ; 
 int MAX_SIZE ; 
 char* MakeCharArray (char,int) ; 
 char* Malloc (int) ; 
 int /*<<< orphan*/  PrintCandidateHelp (TYPE_3__*,char*,TYPE_2__*,int) ; 
 TYPE_1__* SeparateStringByWidth (char*,int) ; 
 int /*<<< orphan*/  UniFormat (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  UniFreeToken (TYPE_1__*) ; 
 char* _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  stub10 (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  stub11 (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  stub12 (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  stub5 (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  stub6 (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  stub7 (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  stub8 (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  stub9 (TYPE_3__*,char*) ; 

void PrintCmdHelp(CONSOLE *c, char *cmd_name, TOKEN_LIST *param_list)
{
	wchar_t tmp[MAX_SIZE];
	wchar_t *buf;
	UINT buf_size;
	wchar_t *description, *args, *help;
	UNI_TOKEN_LIST *t;
	UINT width;
	UINT i;
	char *space;
	// Validate arguments
	if (c == NULL || cmd_name == NULL || param_list == NULL)
	{
		return;
	}

	width = GetConsoleWidth(c) - 2;

	buf_size = sizeof(wchar_t) * (width + 32);
	buf = Malloc(buf_size);

	GetCommandHelpStr(cmd_name, &description, &args, &help);

	space = MakeCharArray(' ', 2);

	// Title
	UniFormat(tmp, sizeof(tmp), _UU("CMD_HELP_TITLE"), cmd_name);
	c->Write(c, tmp);
	c->Write(c, L"");

	// Purpose
	c->Write(c, _UU("CMD_HELP_DESCRIPTION"));
	t = SeparateStringByWidth(description, width - 2);
	for (i = 0;i < t->NumTokens;i++)
	{
		UniFormat(buf, buf_size, L"%S%s", space, t->Token[i]);
		c->Write(c, buf);
	}
	UniFreeToken(t);
	c->Write(c, L"");

	// Description
	c->Write(c, _UU("CMD_HELP_HELP"));
	t = SeparateStringByWidth(help, width - 2);
	for (i = 0;i < t->NumTokens;i++)
	{
		UniFormat(buf, buf_size, L"%S%s", space, t->Token[i]);
		c->Write(c, buf);
	}
	UniFreeToken(t);
	c->Write(c, L"");

	// Usage
	c->Write(c, _UU("CMD_HELP_USAGE"));
	t = SeparateStringByWidth(args, width - 2);
	for (i = 0;i < t->NumTokens;i++)
	{
		UniFormat(buf, buf_size, L"%S%s", space, t->Token[i]);
		c->Write(c, buf);
	}
	UniFreeToken(t);

	// Arguments
	if (param_list->NumTokens >= 1)
	{
		c->Write(c, L"");
		c->Write(c, _UU("CMD_HELP_ARGS"));
		PrintCandidateHelp(c, cmd_name, param_list, 2);
	}

	Free(space);

	Free(buf);
}