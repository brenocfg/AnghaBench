#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ RTC_Seconds; scalar_t__ RTC_Minutes; scalar_t__ RTC_Hours; int /*<<< orphan*/  RTC_H12; } ;
struct TYPE_5__ {int RTC_AlarmDateWeekDay; int /*<<< orphan*/  RTC_AlarmMask; int /*<<< orphan*/  RTC_AlarmDateWeekDaySel; TYPE_1__ RTC_AlarmTime; } ;
typedef  TYPE_2__ RTC_AlarmTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_AlarmDateWeekDaySel_Date ; 
 int /*<<< orphan*/  RTC_AlarmMask_None ; 
 int /*<<< orphan*/  RTC_H12_AM ; 

void RTC_AlarmStructInit(RTC_AlarmTypeDef* RTC_AlarmStruct)
{
  /* Alarm Time Settings : Time = 00h:00mn:00sec */
  RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = RTC_H12_AM;
  RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours = 0;
  RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes = 0;
  RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds = 0;

  /* Alarm Date Settings : Date = 1st day of the month */
  RTC_AlarmStruct->RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
  RTC_AlarmStruct->RTC_AlarmDateWeekDay = 1;

  /* Alarm Masks Settings : Mask =  all fields are not masked */
  RTC_AlarmStruct->RTC_AlarmMask = RTC_AlarmMask_None;
}