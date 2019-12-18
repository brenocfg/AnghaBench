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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_year; int /*<<< orphan*/  tm_wday; int /*<<< orphan*/  tm_mon; } ;
struct TYPE_3__ {int wSecond; int wMinute; int wHour; int wDay; int wMonth; int wYear; int /*<<< orphan*/  wDayOfWeek; } ;
typedef  TYPE_1__ SYSTEMTIME ;

/* Variables and functions */
 int /*<<< orphan*/  GetLocalTime (TYPE_1__*) ; 
 int hex2bcd (int) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gettime(int p)
{
#ifdef HAVE_WINDOWS_H
	SYSTEMTIME st;
	GetLocalTime(&st);
	switch (p) {
	case 0:
		return hex2bcd(st.wSecond);
	case 1:
		return hex2bcd(st.wMinute);
	case 2:
		return hex2bcd(st.wHour);
	case 3:
		return hex2bcd(st.wDay);
	case 4:
		return hex2bcd(st.wMonth);
	case 5:
		return hex2bcd(st.wYear % 100);
	case 6:
		return hex2bcd(((st.wDayOfWeek + 2) % 7) + 1);
	}
#else /* HAVE_WINDOWS_H */
	time_t tt;
	struct tm *lt;

	tt = time(NULL);
	lt = localtime(&tt);

	switch (p) {
	case 0:
		return hex2bcd(lt->tm_sec);
	case 1:
		return hex2bcd(lt->tm_min);
	case 2:
		return hex2bcd(lt->tm_hour);
	case 3:
		return hex2bcd(lt->tm_mday);
	case 4:
		return hex2bcd(lt->tm_mon + 1);
	case 5:
		return hex2bcd(lt->tm_year % 100);
	case 6:
		return hex2bcd(((lt->tm_wday + 2) % 7) + 1);
	}
#endif /* HAVE_WINDOWS_H */
	return 0;
}