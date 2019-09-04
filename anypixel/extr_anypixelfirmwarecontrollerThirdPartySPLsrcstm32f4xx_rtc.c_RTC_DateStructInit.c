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
struct TYPE_3__ {int RTC_Date; scalar_t__ RTC_Year; int /*<<< orphan*/  RTC_Month; int /*<<< orphan*/  RTC_WeekDay; } ;
typedef  TYPE_1__ RTC_DateTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_Month_January ; 
 int /*<<< orphan*/  RTC_Weekday_Monday ; 

void RTC_DateStructInit(RTC_DateTypeDef* RTC_DateStruct)
{
  /* Monday, January 01 xx00 */
  RTC_DateStruct->RTC_WeekDay = RTC_Weekday_Monday;
  RTC_DateStruct->RTC_Date = 1;
  RTC_DateStruct->RTC_Month = RTC_Month_January;
  RTC_DateStruct->RTC_Year = 0;
}