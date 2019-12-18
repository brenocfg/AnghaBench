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
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;

/* Variables and functions */
 int /*<<< orphan*/  ClearStr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemTimeToJsonStr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UINT64ToSystem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void SystemTime64ToJsonStr(char *dst, UINT size, UINT64 t)
{
	SYSTEMTIME st;
	if (dst == NULL)
	{
		return;
	}

	if (t == 0)
	{
		ClearStr(dst, size);
	}

	UINT64ToSystem(&st, t);

	SystemTimeToJsonStr(dst, size, &st);
}