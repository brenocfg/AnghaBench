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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  scalar_t__ UINT ;
struct TYPE_5__ {scalar_t__ Param; } ;
struct TYPE_4__ {int /*<<< orphan*/ * InBuf; } ;
typedef  TYPE_1__ LOCAL_CONSOLE_PARAM ;
typedef  TYPE_2__ CONSOLE ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ CalcUtf8ToUni (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* CfgReadNextLine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int IsEmptyStr (char*) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 
 int /*<<< orphan*/  Utf8ToUni (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ZeroMalloc (scalar_t__) ; 

wchar_t *ConsoleReadNextFromInFile(CONSOLE *c)
{
	LOCAL_CONSOLE_PARAM *p;
	char *str;
	// Validate arguments
	if (c == NULL)
	{
		return NULL;
	}

	p = (LOCAL_CONSOLE_PARAM *)c->Param;

	if (p->InBuf == NULL)
	{
		return NULL;
	}

	while (true)
	{
		str = CfgReadNextLine(p->InBuf);

		if (str == NULL)
		{
			return NULL;
		}

		Trim(str);

		if (IsEmptyStr(str) == false)
		{
			UINT size;
			wchar_t *ret;

			size = CalcUtf8ToUni((BYTE *)str, StrLen(str));
			ret = ZeroMalloc(size + 32);
			Utf8ToUni(ret, size, (BYTE *)str, StrLen(str));

			Free(str);

			return ret;
		}

		Free(str);
	}
}