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
struct TYPE_2__ {scalar_t__ CFGR1; } ;
typedef  scalar_t__ FunctionalState ;

/* Variables and functions */
 scalar_t__ DISABLE ; 
 int /*<<< orphan*/  IS_FUNCTIONAL_STATE (scalar_t__) ; 
 int /*<<< orphan*/  IS_SYSCFG_I2C_FMP (scalar_t__) ; 
 TYPE_1__* SYSCFG ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void SYSCFG_I2CFastModePlusConfig(uint32_t SYSCFG_I2CFastModePlus, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SYSCFG_I2C_FMP(SYSCFG_I2CFastModePlus));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable fast mode plus driving capability for selected pin */
    SYSCFG->CFGR1 |= (uint32_t)SYSCFG_I2CFastModePlus;
  }
  else
  {
    /* Disable fast mode plus driving capability for selected pin */
    SYSCFG->CFGR1 &= (uint32_t)(~SYSCFG_I2CFastModePlus);
  }
}