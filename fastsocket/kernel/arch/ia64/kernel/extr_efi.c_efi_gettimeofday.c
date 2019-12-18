#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_4__ {int /*<<< orphan*/  nanosecond; int /*<<< orphan*/  second; int /*<<< orphan*/  minute; int /*<<< orphan*/  hour; int /*<<< orphan*/  day; int /*<<< orphan*/  month; int /*<<< orphan*/  year; } ;
typedef  TYPE_1__ efi_time_t ;
struct TYPE_5__ {scalar_t__ (* get_time ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ EFI_SUCCESS ; 
 TYPE_3__ efi ; 
 int /*<<< orphan*/  memset (struct timespec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mktime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 

void
efi_gettimeofday (struct timespec *ts)
{
	efi_time_t tm;

	if ((*efi.get_time)(&tm, NULL) != EFI_SUCCESS) {
		memset(ts, 0, sizeof(*ts));
		return;
	}

	ts->tv_sec = mktime(tm.year, tm.month, tm.day,
			    tm.hour, tm.minute, tm.second);
	ts->tv_nsec = tm.nanosecond;
}