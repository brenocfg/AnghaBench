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
typedef  char wchar_t ;
typedef  size_t UINT ;
struct TYPE_4__ {char* name; char* unistr; char* str; } ;
typedef  TYPE_1__ TABLE ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 size_t CalcUniToStr (char*) ; 
 size_t CalcUtf8ToUni (char*,size_t) ; 
 char* CopyUniStr (char*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,size_t) ; 
 size_t LIST_NUM (int /*<<< orphan*/ *) ; 
 void* Malloc (int) ; 
 int /*<<< orphan*/  StrCat (char*,size_t,char*) ; 
 scalar_t__ StrCmpi (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,size_t,char*) ; 
 size_t StrLen (char*) ; 
 int /*<<< orphan*/  StrUpper (char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 
 int /*<<< orphan*/  TrimLeft (char*) ; 
 int /*<<< orphan*/  UnescapeStr (char*) ; 
 scalar_t__ UniInChar (char*,int) ; 
 int /*<<< orphan*/  UniReplaceStrEx (char*,size_t,char*,char*,char*,int) ; 
 int /*<<< orphan*/  UniStrCpy (char*,size_t,char*) ; 
 int UniStrSize (char*) ; 
 int /*<<< orphan*/  UniToStr (char*,size_t,char*) ; 
 int /*<<< orphan*/  Utf8ToUni (char*,size_t,char*,size_t) ; 
 char* ZeroMalloc (size_t) ; 

TABLE *ParseTableLine(char *line, char *prefix, UINT prefix_size, LIST *replace_list)
{
	UINT i, len;
	UINT len_name;
	UINT string_start;
	char *name;
	char *name2;
	UINT name2_size;
	wchar_t *unistr;
	char *str;
	UINT unistr_size, str_size;
	TABLE *t;
	// Validate arguments
	if (line == NULL || prefix == NULL)
	{
		return NULL;
	}
	TrimLeft(line);

	// No line
	len = StrLen(line);
	if (len == 0)
	{
		return NULL;
	}

	// Comment
	if (line[0] == '#' || (line[0] == '/' && line[1] == '/'))
	{
		return NULL;
	}

	// Search to the end position of the name
	len_name = 0;
	for (i = 0;;i++)
	{
		if (line[i] == 0)
		{
			// There is only one token
			return NULL;
		}
		if (line[i] == ' ' || line[i] == '\t')
		{
			break;
		}
		len_name++;
	}

	name = Malloc(len_name + 1);
	StrCpy(name, len_name + 1, line);

	string_start = len_name;
	for (i = len_name;i < len;i++)
	{
		if (line[i] != ' ' && line[i] != '\t')
		{
			break;
		}
		string_start++;
	}
	if (i == len)
	{
		Free(name);
		return NULL;
	}

	// Unescape
	UnescapeStr(&line[string_start]);

	// Convert to Unicode
	unistr_size = CalcUtf8ToUni(&line[string_start], StrLen(&line[string_start]));
	if (unistr_size == 0)
	{
		Free(name);
		return NULL;
	}
	unistr = Malloc(unistr_size);
	Utf8ToUni(unistr, unistr_size, &line[string_start], StrLen(&line[string_start]));

	if (UniInChar(unistr, L'$'))
	{
		// Replace the replacement string
		wchar_t *tmp;
		UINT tmp_size = (UniStrSize(unistr) + 1024) * 2;
		UINT i;

		tmp = Malloc(tmp_size);

		UniStrCpy(tmp, tmp_size, unistr);

		for (i = 0; i < LIST_NUM(replace_list);i++)
		{
			TABLE *r = LIST_DATA(replace_list, i);

			UniReplaceStrEx(tmp, tmp_size, tmp, (wchar_t *)r->name, r->unistr, false);
		}

		Free(unistr);

		unistr = CopyUniStr(tmp);

		Free(tmp);
	}

	// Convert to ANSI
	str_size = CalcUniToStr(unistr);
	if (str_size == 0)
	{
		str_size = 1;
		str = Malloc(1);
		str[0] = 0;
	}
	else
	{
		str = Malloc(str_size);
		UniToStr(str, str_size, unistr);
	}

	if (StrCmpi(name, "PREFIX") == 0)
	{
		// Prefix is specified
		StrCpy(prefix, prefix_size, str);
		Trim(prefix);

		if (StrCmpi(prefix, "$") == 0 || StrCmpi(prefix, "NULL") == 0)
		{
			prefix[0] = 0;
		}

		Free(name);
		Free(str);
		Free(unistr);

		return NULL;
	}

	name2_size = StrLen(name) + StrLen(prefix) + 2;
	name2 = ZeroMalloc(name2_size);

	if (prefix[0] != 0)
	{
		StrCat(name2, name2_size, prefix);
		StrCat(name2, name2_size, "@");
	}

	StrCat(name2, name2_size, name);

	Free(name);

	// Create a TABLE
	t = Malloc(sizeof(TABLE));
	StrUpper(name2);
	t->name = name2;
	t->str = str;
	t->unistr = unistr;

	return t;
}