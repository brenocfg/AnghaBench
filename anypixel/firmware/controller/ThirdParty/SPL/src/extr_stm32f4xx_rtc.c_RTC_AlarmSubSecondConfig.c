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
struct TYPE_2__ {int WPR; scalar_t__ ALRMBSSR; scalar_t__ ALRMASSR; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_RTC_ALARM (scalar_t__) ; 
 int /*<<< orphan*/  IS_RTC_ALARM_SUB_SECOND_MASK (scalar_t__) ; 
 int /*<<< orphan*/  IS_RTC_ALARM_SUB_SECOND_VALUE (scalar_t__) ; 
 TYPE_1__* RTC ; 
 scalar_t__ RTC_Alarm_A ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void RTC_AlarmSubSecondConfig(uint32_t RTC_Alarm, uint32_t RTC_AlarmSubSecondValue, uint32_t RTC_AlarmSubSecondMask)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RTC_ALARM(RTC_Alarm));
  assert_param(IS_RTC_ALARM_SUB_SECOND_VALUE(RTC_AlarmSubSecondValue));
  assert_param(IS_RTC_ALARM_SUB_SECOND_MASK(RTC_AlarmSubSecondMask));
  
  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;
  
  /* Configure the Alarm A or Alarm B SubSecond registers */
  tmpreg = (uint32_t) (uint32_t)(RTC_AlarmSubSecondValue) | (uint32_t)(RTC_AlarmSubSecondMask);
  
  if (RTC_Alarm == RTC_Alarm_A)
  {
    /* Configure the AlarmA SubSecond register */
    RTC->ALRMASSR = tmpreg;
  }
  else
  {
    /* Configure the Alarm B SubSecond register */
    RTC->ALRMBSSR = tmpreg;
  }

  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;

}