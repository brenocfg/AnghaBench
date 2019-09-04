#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int ALRMASSR; int ALRMBSSR; } ;

/* Variables and functions */
 TYPE_1__* RTC ; 
 int RTC_ALRMASSR_SS ; 
 int RTC_ALRMBSSR_SS ; 
 scalar_t__ RTC_Alarm_A ; 

uint32_t RTC_GetAlarmSubSecond(uint32_t RTC_Alarm)
{
  uint32_t tmpreg = 0;
  
  /* Get the RTC_ALRMxR register */
  if (RTC_Alarm == RTC_Alarm_A)
  {
    tmpreg = (uint32_t)((RTC->ALRMASSR) & RTC_ALRMASSR_SS);
  }
  else
  {
    tmpreg = (uint32_t)((RTC->ALRMBSSR) & RTC_ALRMBSSR_SS);
  } 
  
  return (tmpreg);
}