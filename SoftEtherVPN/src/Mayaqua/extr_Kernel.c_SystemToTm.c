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
struct tm {int tm_isdst; void* tm_sec; void* tm_min; void* tm_hour; void* tm_mday; void* tm_mon; void* tm_year; } ;
struct TYPE_3__ {int /*<<< orphan*/  wSecond; int /*<<< orphan*/  wMinute; int /*<<< orphan*/  wHour; int /*<<< orphan*/  wDay; int /*<<< orphan*/  wMonth; int /*<<< orphan*/  wYear; } ;
typedef  TYPE_1__ SYSTEMTIME ;

/* Variables and functions */
 void* MAKESURE (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  NormalizeTm (struct tm*) ; 
 int /*<<< orphan*/  Zero (struct tm*,int) ; 

void SystemToTm(struct tm *t, SYSTEMTIME *st)
{
	// Validate arguments
	if (t == NULL || st == NULL)
	{
		return;
	}

	Zero(t, sizeof(struct tm));
	t->tm_year = MAKESURE(st->wYear, 1970, 2099) - 1900;
	t->tm_mon = MAKESURE(st->wMonth, 1, 12) - 1;
	t->tm_mday = MAKESURE(st->wDay, 1, 31);
	t->tm_hour = MAKESURE(st->wHour, 0, 23);
	t->tm_min = MAKESURE(st->wMinute, 0, 59);
	t->tm_sec = MAKESURE(st->wSecond, 0, 59);

	t->tm_isdst = -1;
	NormalizeTm(t);
}