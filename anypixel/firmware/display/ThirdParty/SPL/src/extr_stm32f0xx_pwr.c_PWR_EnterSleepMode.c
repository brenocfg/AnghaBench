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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ SCR; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_PWR_SLEEP_ENTRY (scalar_t__) ; 
 scalar_t__ PWR_SLEEPEntry_WFI ; 
 TYPE_1__* SCB ; 
 scalar_t__ SCB_SCR_SLEEPDEEP_Msk ; 
 int /*<<< orphan*/  __WFE () ; 
 int /*<<< orphan*/  __WFI () ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void PWR_EnterSleepMode(uint8_t PWR_SLEEPEntry)
{
  /* Check the parameters */
  assert_param(IS_PWR_SLEEP_ENTRY(PWR_SLEEPEntry));

  /* Clear SLEEPDEEP bit of Cortex-M0 System Control Register */
  SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
  
  /* Select SLEEP mode entry -------------------------------------------------*/
  if(PWR_SLEEPEntry == PWR_SLEEPEntry_WFI)
  {
    /* Request Wait For Interrupt */
    __WFI();
  }
  else
  {
    /* Request Wait For Event */
    __WFE();
  }
}