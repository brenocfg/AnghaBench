#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_10__ {int NumTokens; int /*<<< orphan*/ * Token; } ;
typedef  TYPE_1__ UNI_TOKEN_LIST ;
typedef  int UINT ;
struct TYPE_12__ {int /*<<< orphan*/  (* Write ) (TYPE_3__*,char*) ;} ;
struct TYPE_11__ {int NumTokens; char** Token; } ;
typedef  TYPE_2__ TOKEN_LIST ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_3__ CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/ * CompareCandidateStr ; 
 int /*<<< orphan*/  Format (char*,int,char*,char*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  GetCommandHelpStr (char*,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetCommandParamHelpStr (char*,char*,char**) ; 
 int GetConsoleWidth (TYPE_3__*) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ *,char*) ; 
 char* LIST_DATA (int /*<<< orphan*/ *,int) ; 
 int LIST_NUM (int /*<<< orphan*/ *) ; 
 int MAX (int,int) ; 
 char* MakeCharArray (char,int) ; 
 char* Malloc (int) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 TYPE_1__* SeparateStringByWidth (char*,int) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int StrLen (char*) ; 
 int StrWidth (char*) ; 
 int /*<<< orphan*/  UniFormat (char*,int,char*,char*,char*,char*,...) ; 
 int /*<<< orphan*/  UniFreeToken (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,char*) ; 

void PrintCandidateHelp(CONSOLE *c, char *cmd_name, TOKEN_LIST *candidate_list, UINT left_space)
{
	UINT console_width;
	UINT max_keyword_width;
	LIST *o;
	UINT i;
	wchar_t *tmpbuf;
	UINT tmpbuf_size;
	char *left_space_array;
	char *max_space_array;
	// Validate arguments
	if (c == NULL || candidate_list == NULL)
	{
		return;
	}

	// Get the width of the screen
	console_width = GetConsoleWidth(c) - 1;

	tmpbuf_size = sizeof(wchar_t) * (console_width + 32);
	tmpbuf = Malloc(tmpbuf_size);

	left_space_array = MakeCharArray(' ', left_space);

	// Sort and enlist the command name
	// no need to sort the parameter name
	o = NewListFast(cmd_name == NULL ? CompareCandidateStr : NULL);

	max_keyword_width = 0;

	for (i = 0;i < candidate_list->NumTokens;i++)
	{
		UINT keyword_width;

		// Get the width of each keyword
		Insert(o, candidate_list->Token[i]);

		keyword_width = StrWidth(candidate_list->Token[i]);
		if (cmd_name != NULL)
		{
			if (candidate_list->Token[i][0] != '[')
			{
				keyword_width += 1;
			}
			else
			{
				keyword_width -= 2;
			}
		}

		max_keyword_width = MAX(max_keyword_width, keyword_width);
	}

	max_space_array = MakeCharArray(' ', max_keyword_width);

	// Display the candidate
	for (i = 0;i < LIST_NUM(o);i++)
	{
		char tmp[128];
		char *name = LIST_DATA(o, i);
		UNI_TOKEN_LIST *t;
		wchar_t *help;
		UINT j;
		UINT keyword_start_width = left_space;
		UINT descript_start_width = left_space + max_keyword_width + 1;
		UINT descript_width;
		char *space;

		if (console_width >= (descript_start_width + 5))
		{
			descript_width = console_width - descript_start_width - 3;
		}
		else
		{
			descript_width = 2;
		}

		// Generate the name
		if (cmd_name != NULL && name[0] != '[')
		{
			// Prepend a "/" in the case of a parameter
			Format(tmp, sizeof(tmp), "/%s", name);
		}
		else
		{
			// Use the characters as it is in the case of a command name
			if (cmd_name == NULL)
			{
				StrCpy(tmp, sizeof(tmp), name);
			}
			else
			{
				StrCpy(tmp, sizeof(tmp), name + 1);
				if (StrLen(tmp) >= 1)
				{
					tmp[StrLen(tmp) - 1] = 0;
				}
			}
		}

		// Get the help string
		if (cmd_name == NULL)
		{
			GetCommandHelpStr(name, &help, NULL, NULL);
		}
		else
		{
			GetCommandParamHelpStr(cmd_name, name, &help);
		}

		space = MakeCharArray(' ', max_keyword_width - StrWidth(name) - (cmd_name == NULL ? 0 : (name[0] != '[' ? 1 : -2)));

		t = SeparateStringByWidth(help, descript_width);

		for (j = 0;j < t->NumTokens;j++)
		{
			if (j == 0)
			{
				UniFormat(tmpbuf, tmpbuf_size, L"%S%S%S - %s",
					left_space_array, tmp, space, t->Token[j]);
			}
			else
			{
				UniFormat(tmpbuf, tmpbuf_size, L"%S%S   %s",
					left_space_array, max_space_array, t->Token[j]);
			}

			c->Write(c, tmpbuf);
		}

		Free(space);

		UniFreeToken(t);
	}

	ReleaseList(o);

	Free(max_space_array);
	Free(tmpbuf);
	Free(left_space_array);
}