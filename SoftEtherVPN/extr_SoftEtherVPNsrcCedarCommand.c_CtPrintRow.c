#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  size_t UINT ;
struct TYPE_6__ {int (* GetWidth ) (TYPE_1__*) ;int /*<<< orphan*/  (* Write ) (TYPE_1__*,char*) ;} ;
typedef  TYPE_1__ CONSOLE ;

/* Variables and functions */
 char* CopyStrToUni (char*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 char* MakeCharArray (char,size_t) ; 
 int /*<<< orphan*/  StrToUni (char*,int,char*) ; 
 int /*<<< orphan*/  UniStrCat (char*,size_t,char*) ; 
 scalar_t__ UniStrCmpi (char*,char*) ; 
 int UniStrLen (char*) ; 
 size_t UniStrWidth (char*) ; 
 int /*<<< orphan*/  UniTrimRight (char*) ; 
 char* ZeroMalloc (size_t) ; 
 int stub1 (TYPE_1__*) ; 
 int stub2 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,char*) ; 

void CtPrintRow(CONSOLE *c, UINT num, UINT *widths, wchar_t **strings, bool *rights, char separate_char)
{
	UINT i;
	wchar_t *buf;
	UINT buf_size;
	bool is_sep_line = true;
	// Validate arguments
	if (c == NULL || num == 0 || widths == NULL || strings == NULL || rights == NULL)
	{
		return;
	}

	buf_size = 32;
	for (i = 0;i < num;i++)
	{
		buf_size += sizeof(wchar_t) * widths[i] + 6;
	}

	buf = ZeroMalloc(buf_size);

	for (i = 0;i < num;i++)
	{
		char *tmp;
		wchar_t *space_string;
		UINT w;
		UINT space = 0;
		wchar_t *string = strings[i];
		wchar_t *tmp_line = NULL;

		if (UniStrCmpi(string, L"---") == 0)
		{
			char *s = MakeCharArray('-', widths[i]);
			tmp_line = string = CopyStrToUni(s);

			Free(s);
		}
		else
		{
			is_sep_line = false;
		}

		w = UniStrWidth(string);

		if (widths[i] >= w)
		{
			space = widths[i] - w;
		}

		tmp = MakeCharArray(' ', space);
		space_string = CopyStrToUni(tmp);

		if (rights[i] != false)
		{
			UniStrCat(buf, buf_size, space_string);
		}

		UniStrCat(buf, buf_size, string);

		if (rights[i] == false)
		{
			UniStrCat(buf, buf_size, space_string);
		}

		Free(space_string);
		Free(tmp);

		if (i < (num - 1))
		{
			wchar_t tmp[4];
			char str[2];

			if (UniStrCmpi(strings[i], L"---") == 0)
			{
				str[0] = '+';
			}
			else
			{
				str[0] = separate_char;
			}
			str[1] = 0;

			StrToUni(tmp, sizeof(tmp), str);

			UniStrCat(buf, buf_size, tmp);
		}

		if (tmp_line != NULL)
		{
			Free(tmp_line);
		}
	}

	UniTrimRight(buf);

	if (is_sep_line)
	{
		if (UniStrLen(buf) > (c->GetWidth(c) - 1))
		{
			buf[c->GetWidth(c) - 1] = 0;
		}
	}

	c->Write(c, buf);

	Free(buf);
}