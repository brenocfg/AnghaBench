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
struct TYPE_2__ {int WPR; scalar_t__ WUTR; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_RTC_WAKEUP_COUNTER (scalar_t__) ; 
 TYPE_1__* RTC ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void RTC_SetWakeUpCounter(uint32_t RTC_WakeUpCounter)
{
  /* Check the parameters */
  assert_param(IS_RTC_WAKEUP_COUNTER(RTC_WakeUpCounter));
  
  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;
  
  /* Configure the Wakeup Timer counter */
  RTC->WUTR = (uint32_t)RTC_WakeUpCounter;
  
  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;
}