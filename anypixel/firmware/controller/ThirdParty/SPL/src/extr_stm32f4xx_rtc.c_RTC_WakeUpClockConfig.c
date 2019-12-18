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
struct TYPE_2__ {int WPR; scalar_t__ CR; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_RTC_WAKEUP_CLOCK (scalar_t__) ; 
 TYPE_1__* RTC ; 
 scalar_t__ RTC_CR_WUCKSEL ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void RTC_WakeUpClockConfig(uint32_t RTC_WakeUpClock)
{
  /* Check the parameters */
  assert_param(IS_RTC_WAKEUP_CLOCK(RTC_WakeUpClock));

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  /* Clear the Wakeup Timer clock source bits in CR register */
  RTC->CR &= (uint32_t)~RTC_CR_WUCKSEL;

  /* Configure the clock source */
  RTC->CR |= (uint32_t)RTC_WakeUpClock;
  
  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF; 
}