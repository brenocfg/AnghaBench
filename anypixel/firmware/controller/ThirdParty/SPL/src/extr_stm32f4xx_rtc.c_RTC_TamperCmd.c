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
typedef  scalar_t__ FunctionalState ;

/* Variables and functions */
 scalar_t__ DISABLE ; 
 int /*<<< orphan*/  IS_FUNCTIONAL_STATE (scalar_t__) ; 
 int /*<<< orphan*/  IS_RTC_TAMPER (scalar_t__) ; 
 TYPE_1__* RTC ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void RTC_TamperCmd(uint32_t RTC_Tamper, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RTC_TAMPER(RTC_Tamper));  
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the selected Tamper pin */
    RTC->TAFCR |= (uint32_t)RTC_Tamper;
  }
  else
  {
    /* Disable the selected Tamper pin */
    RTC->TAFCR &= (uint32_t)~RTC_Tamper;    
  }  
}