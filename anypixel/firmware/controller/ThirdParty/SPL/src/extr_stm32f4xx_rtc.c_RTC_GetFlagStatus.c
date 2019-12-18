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
struct TYPE_2__ {int ISR; } ;
typedef  scalar_t__ FlagStatus ;

/* Variables and functions */
 int /*<<< orphan*/  IS_RTC_GET_FLAG (int) ; 
 scalar_t__ RESET ; 
 TYPE_1__* RTC ; 
 int RTC_FLAGS_MASK ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

FlagStatus RTC_GetFlagStatus(uint32_t RTC_FLAG)
{
  FlagStatus bitstatus = RESET;
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_RTC_GET_FLAG(RTC_FLAG));
  
  /* Get all the flags */
  tmpreg = (uint32_t)(RTC->ISR & RTC_FLAGS_MASK);
  
  /* Return the status of the flag */
  if ((tmpreg & RTC_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}