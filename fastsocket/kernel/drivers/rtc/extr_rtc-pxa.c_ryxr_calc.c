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
typedef  int u32 ;
struct rtc_time {int tm_year; int tm_mon; int tm_mday; } ;

/* Variables and functions */
 int RYxR_MONTH_S ; 
 int RYxR_YEAR_S ; 

__attribute__((used)) static u32 ryxr_calc(struct rtc_time *tm)
{
	return ((tm->tm_year + 1900) << RYxR_YEAR_S)
		| ((tm->tm_mon + 1) << RYxR_MONTH_S)
		| tm->tm_mday;
}