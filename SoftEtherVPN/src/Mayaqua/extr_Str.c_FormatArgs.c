#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int /*<<< orphan*/ * CopyStrToUni (char*) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * InternalFormatArgs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UniToStr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void FormatArgs(char *buf, UINT size, char *fmt, va_list args)
{
	wchar_t *tag;
	wchar_t *ret;
	// Validate arguments
	if (buf == NULL || fmt == NULL)
	{
		return;
	}

	tag = CopyStrToUni(fmt);
	ret = InternalFormatArgs(tag, args, true);

	UniToStr(buf, size, ret);
	Free(ret);
	Free(tag);
}