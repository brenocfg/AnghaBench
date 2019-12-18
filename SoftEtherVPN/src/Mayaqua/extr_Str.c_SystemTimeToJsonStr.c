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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;

/* Variables and functions */
 int /*<<< orphan*/  ClearStr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDateTimeStrRFC3339 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void SystemTimeToJsonStr(char *dst, UINT size, SYSTEMTIME *t)
{
	if (dst == NULL)
	{
		return;
	}

	if (t == NULL)
	{
		ClearStr(dst, size);
	}
	else
	{
		GetDateTimeStrRFC3339(dst, size, t, 0);
	}
}