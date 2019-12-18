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
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {size_t wDayOfWeek; int wMonth; int /*<<< orphan*/  wSecond; int /*<<< orphan*/  wMinute; int /*<<< orphan*/  wHour; int /*<<< orphan*/  wYear; int /*<<< orphan*/  wDay; } ;
typedef  TYPE_1__ SYSTEMTIME ;

/* Variables and functions */
 int /*<<< orphan*/  Format (char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT64ToSystem (TYPE_1__*,int /*<<< orphan*/ ) ; 

void GetHttpDateStr(char *str, UINT size, UINT64 t)
{
	SYSTEMTIME s;
	static char *wday[] =
	{
		"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat",
	};
	static char *month[] =
	{
		"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct",
		"Nov", "Dec",
	};
	// Validate arguments
	if (str == NULL)
	{
		return;
	}
	UINT64ToSystem(&s, t);

	Format(str, size, "%s, %02u %s %04u %02u:%02u:%02u GMT",
		wday[s.wDayOfWeek], s.wDay, month[s.wMonth - 1], s.wYear,
		s.wHour, s.wMinute, s.wSecond);
}