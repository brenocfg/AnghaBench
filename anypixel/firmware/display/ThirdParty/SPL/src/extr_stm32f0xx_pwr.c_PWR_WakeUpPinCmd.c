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
struct TYPE_2__ {int /*<<< orphan*/  CSR; } ;
typedef  scalar_t__ FunctionalState ;

/* Variables and functions */
 scalar_t__ DISABLE ; 
 int /*<<< orphan*/  IS_FUNCTIONAL_STATE (scalar_t__) ; 
 int /*<<< orphan*/  IS_PWR_WAKEUP_PIN (int /*<<< orphan*/ ) ; 
 TYPE_1__* PWR ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void PWR_WakeUpPinCmd(uint32_t PWR_WakeUpPin, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_PWR_WAKEUP_PIN(PWR_WakeUpPin));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the EWUPx pin */
    PWR->CSR |= PWR_WakeUpPin;
  }
  else
  {
    /* Disable the EWUPx pin */
    PWR->CSR &= ~PWR_WakeUpPin;
  }
}