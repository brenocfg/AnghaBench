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
struct TYPE_2__ {scalar_t__ TAFCR; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_RTC_TAMPER_SAMPLING_FREQ (scalar_t__) ; 
 TYPE_1__* RTC ; 
 scalar_t__ RTC_TAFCR_TAMPFREQ ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void RTC_TamperSamplingFreqConfig(uint32_t RTC_TamperSamplingFreq)
{
  /* Check the parameters */
  assert_param(IS_RTC_TAMPER_SAMPLING_FREQ(RTC_TamperSamplingFreq));
 
  /* Clear TAMPFREQ[2:0] bits in the RTC_TAFCR register */
  RTC->TAFCR &= (uint32_t)~(RTC_TAFCR_TAMPFREQ);

  /* Configure the RTC_TAFCR register */
  RTC->TAFCR |= (uint32_t)RTC_TamperSamplingFreq;
}