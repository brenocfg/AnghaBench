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
typedef  int /*<<< orphan*/  u32 ;
struct rtc_time {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtc_bfin_to_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_time_to_tm (int /*<<< orphan*/ ,struct rtc_time*) ; 

__attribute__((used)) static inline void rtc_bfin_to_tm(u32 rtc_bfin, struct rtc_time *tm)
{
	rtc_time_to_tm(rtc_bfin_to_time(rtc_bfin), tm);
}