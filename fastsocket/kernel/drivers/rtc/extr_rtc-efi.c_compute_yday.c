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
struct TYPE_3__ {int /*<<< orphan*/  year; scalar_t__ month; scalar_t__ day; } ;
typedef  TYPE_1__ efi_time_t ;

/* Variables and functions */
 int rtc_year_days (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
compute_yday(efi_time_t *eft)
{
	/* efi_time_t.month is in the [1-12] so, we need -1 */
	return rtc_year_days(eft->day - 1, eft->month - 1, eft->year);
}