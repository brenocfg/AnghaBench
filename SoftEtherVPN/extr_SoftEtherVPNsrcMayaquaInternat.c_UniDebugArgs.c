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

/* Variables and functions */
 int /*<<< orphan*/  UniPrintArgs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int g_debug ; 

void UniDebugArgs(wchar_t *fmt, va_list args)
{
	if (g_debug == false)
	{
		return;
	}

	UniPrintArgs(fmt, args);
}