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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  TAFCR; } ;
typedef  scalar_t__ FunctionalState ;

/* Variables and functions */
 scalar_t__ DISABLE ; 
 int /*<<< orphan*/  IS_FUNCTIONAL_STATE (scalar_t__) ; 
 TYPE_1__* RTC ; 
 scalar_t__ RTC_TAFCR_TAMPPUDIS ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void RTC_TamperPullUpCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
 if (NewState != DISABLE)
  {
    /* Enable precharge of the selected Tamper pin */
    RTC->TAFCR &= (uint32_t)~RTC_TAFCR_TAMPPUDIS; 
  }
  else
  {
    /* Disable precharge of the selected Tamper pin */
    RTC->TAFCR |= (uint32_t)RTC_TAFCR_TAMPPUDIS;    
  } 
}