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
 int /*<<< orphan*/  GetTimeStrMilli (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ LocalToSystem64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ SystemToLocal64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT64ToSystem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void GetTimeStrMilli64(char *str, UINT size, UINT64 sec64)
{
	SYSTEMTIME st;
	if (sec64 == 0 || SystemToLocal64(sec64) == 0 || LocalToSystem64(sec64) == 0)
	{
		StrCpy(str, size, "(Unknown)");
		return;
	}
	UINT64ToSystem(&st, sec64);
	GetTimeStrMilli(str, size, &st);
}