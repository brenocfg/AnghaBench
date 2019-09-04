#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/  wMilliseconds; int /*<<< orphan*/  wSecond; int /*<<< orphan*/  wMinute; int /*<<< orphan*/  wHour; } ;
typedef  TYPE_1__ SYSTEMTIME ;

/* Variables and functions */
 int /*<<< orphan*/  Format (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void GetTimeStrMilli(char *str, UINT size, SYSTEMTIME *st)
{
	// Validate arguments
	if (st == NULL || str == NULL)
	{
		return;
	}

	Format(str, size, "%02u:%02u:%02u.%03u",
		st->wHour, st->wMinute, st->wSecond, st->wMilliseconds);
}