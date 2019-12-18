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
struct TYPE_4__ {scalar_t__ generation; int /*<<< orphan*/  shift; int /*<<< orphan*/  scale; int /*<<< orphan*/  ns_base; int /*<<< orphan*/  tsc_base; } ;
typedef  TYPE_1__ pm_rtc_nanotime_t ;
struct TYPE_5__ {scalar_t__ generation; int /*<<< orphan*/  shift; int /*<<< orphan*/  scale; int /*<<< orphan*/  ns_base; int /*<<< orphan*/  tsc_base; } ;

/* Variables and functions */
 TYPE_3__ pal_rtc_nanotime_info ; 

__attribute__((used)) static void
pmGetNanotimeInfo(pm_rtc_nanotime_t *rtc_nanotime)
{
	/*
	 * Make sure that nanotime didn't change while we were reading it.
	 */
	do {
		rtc_nanotime->generation = pal_rtc_nanotime_info.generation; /* must be first */
		rtc_nanotime->tsc_base = pal_rtc_nanotime_info.tsc_base;
		rtc_nanotime->ns_base = pal_rtc_nanotime_info.ns_base;
		rtc_nanotime->scale = pal_rtc_nanotime_info.scale;
		rtc_nanotime->shift = pal_rtc_nanotime_info.shift;
	} while(pal_rtc_nanotime_info.generation != 0
		&& rtc_nanotime->generation != pal_rtc_nanotime_info.generation);
}