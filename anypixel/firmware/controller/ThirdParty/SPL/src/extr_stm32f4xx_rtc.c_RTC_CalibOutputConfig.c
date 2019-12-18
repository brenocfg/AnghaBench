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
 int /*<<< orphan*/  IS_RTC_CALIB_OUTPUT (scalar_t__) ; 
 TYPE_1__* RTC ; 
 scalar_t__ RTC_CR_COSEL ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void RTC_CalibOutputConfig(uint32_t RTC_CalibOutput)
{
  /* Check the parameters */
  assert_param(IS_RTC_CALIB_OUTPUT(RTC_CalibOutput));

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;
  
  /*clear flags before config*/
  RTC->CR &= (uint32_t)~(RTC_CR_COSEL);

  /* Configure the RTC_CR register */
  RTC->CR |= (uint32_t)RTC_CalibOutput;

  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;
}