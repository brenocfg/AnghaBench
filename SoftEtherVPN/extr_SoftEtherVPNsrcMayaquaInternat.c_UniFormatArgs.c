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
typedef  int UINT ;

/* Variables and functions */
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * InternalFormatArgs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KS_FORMAT_COUNT ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

void UniFormatArgs(wchar_t *buf, UINT size, wchar_t *fmt, va_list args)
{
	wchar_t *ret;
	// Validate arguments
	if (buf == NULL || fmt == NULL)
	{
		return;
	}
	if (size == 1)
	{
		return;
	}

	// KS
	KS_INC(KS_FORMAT_COUNT);

	ret = InternalFormatArgs(fmt, args, false);

	UniStrCpy(buf, size, ret);

	Free(ret);
}