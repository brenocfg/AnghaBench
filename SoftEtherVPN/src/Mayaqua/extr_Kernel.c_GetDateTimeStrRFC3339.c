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
struct TYPE_3__ {int /*<<< orphan*/  wMilliseconds; int /*<<< orphan*/  wSecond; int /*<<< orphan*/  wMinute; int /*<<< orphan*/  wHour; int /*<<< orphan*/  wDay; int /*<<< orphan*/  wMonth; int /*<<< orphan*/  wYear; } ;
typedef  TYPE_1__ SYSTEMTIME ;

/* Variables and functions */
 int /*<<< orphan*/  ClearStr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Format (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

void GetDateTimeStrRFC3339(char *str, UINT size, SYSTEMTIME *st, int timezone_min){
	// Validate arguments
	if (str == NULL || st == NULL)
	{
		ClearStr(str, size);
		return;
	}

	if(timezone_min == 0){
		Format(str, size, "%04u-%02u-%02uT%02u:%02u:%02u.%03uZ",
		st->wYear, st->wMonth, st->wDay,
		st->wHour, st->wMinute, st->wSecond,
		st->wMilliseconds);
	}else{
		Format(str, size, "%04u-%02u-%02uT%02u:%02u:%02u.%03u%+02d:%02d",
		st->wYear, st->wMonth, st->wDay,
		st->wHour, st->wMinute, st->wSecond,
		st->wMilliseconds, timezone_min/60, timezone_min%60);
	}
}