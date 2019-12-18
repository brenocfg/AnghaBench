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
typedef  int uint32_t ;
struct TYPE_2__ {int WPR; int CR; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_RTC_DAYLIGHT_SAVING (int) ; 
 int /*<<< orphan*/  IS_RTC_STORE_OPERATION (int) ; 
 TYPE_1__* RTC ; 
 scalar_t__ RTC_CR_BCK ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void RTC_DayLightSavingConfig(uint32_t RTC_DayLightSaving, uint32_t RTC_StoreOperation)
{
  /* Check the parameters */
  assert_param(IS_RTC_DAYLIGHT_SAVING(RTC_DayLightSaving));
  assert_param(IS_RTC_STORE_OPERATION(RTC_StoreOperation));

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  /* Clear the bits to be configured */
  RTC->CR &= (uint32_t)~(RTC_CR_BCK);

  /* Configure the RTC_CR register */
  RTC->CR |= (uint32_t)(RTC_DayLightSaving | RTC_StoreOperation);

  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF; 
}