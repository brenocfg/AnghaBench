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
struct TYPE_2__ {int /*<<< orphan*/  CR; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_PWR_REGULATOR_VOLTAGE (scalar_t__) ; 
 TYPE_1__* PWR ; 
 int /*<<< orphan*/  PWR_Regulator_Voltage_Scale1 ; 
 scalar_t__ PWR_Regulator_Voltage_Scale2 ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void PWR_MainRegulatorModeConfig(uint32_t PWR_Regulator_Voltage)
{
  /* Check the parameters */
  assert_param(IS_PWR_REGULATOR_VOLTAGE(PWR_Regulator_Voltage));

  if (PWR_Regulator_Voltage == PWR_Regulator_Voltage_Scale2)
  {
    PWR->CR &= ~PWR_Regulator_Voltage_Scale1;
  }
  else
  {    
    PWR->CR |= PWR_Regulator_Voltage_Scale1;
  }
}