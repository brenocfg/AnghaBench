#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  scalar_t__ UINT ;
typedef  char UCHAR ;
struct TYPE_5__ {scalar_t__ Param; } ;
struct TYPE_4__ {int /*<<< orphan*/ * OutFile; } ;
typedef  TYPE_1__ LOCAL_CONSOLE_PARAM ;
typedef  TYPE_2__ CONSOLE ;

/* Variables and functions */
 scalar_t__ CalcUniToUtf8 (char*) ; 
 int /*<<< orphan*/  FileWrite (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  Free (char*) ; 
 scalar_t__ StrLen (char*) ; 
 int UniEndWith (char*,char*) ; 
 char* UniNormalizeCrlf (char*) ; 
 int /*<<< orphan*/  UniToUtf8 (char*,scalar_t__,char*) ; 
 char* ZeroMalloc (scalar_t__) ; 

void ConsoleWriteOutFile(CONSOLE *c, wchar_t *str, bool add_last_crlf)
{
	LOCAL_CONSOLE_PARAM *p;
	// Validate arguments
	if (c == NULL || str == NULL)
	{
		return;
	}

	p = (LOCAL_CONSOLE_PARAM *)c->Param;

	if (p != NULL && p->OutFile != NULL)
	{
		wchar_t *tmp = UniNormalizeCrlf(str);
		UINT utf8_size;
		UCHAR *utf8;

		utf8_size = CalcUniToUtf8(tmp);
		utf8 = ZeroMalloc(utf8_size + 1);
		UniToUtf8(utf8, utf8_size + 1, tmp);

		FileWrite(p->OutFile, utf8, utf8_size);

		if (UniEndWith(str, L"\n") == false && add_last_crlf)
		{
			char *crlf = "\r\n";
			FileWrite(p->OutFile, "\r\n", StrLen(crlf));
		}

		Free(utf8);
		Free(tmp);
	}

}