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
struct TYPE_2__ {int ALRMASSR; } ;

/* Variables and functions */
 TYPE_1__* RTC ; 
 int RTC_ALRMASSR_SS ; 

uint32_t RTC_GetAlarmSubSecond(uint32_t RTC_Alarm)
{
  uint32_t tmpreg = 0;
  
  /* Get the RTC_ALRMAR register */
  tmpreg = (uint32_t)((RTC->ALRMASSR) & RTC_ALRMASSR_SS);

  return (tmpreg);
}