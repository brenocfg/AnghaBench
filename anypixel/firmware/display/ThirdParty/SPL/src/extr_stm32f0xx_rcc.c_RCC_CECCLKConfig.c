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
struct TYPE_2__ {int /*<<< orphan*/  CFGR3; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_RCC_CECCLK (int /*<<< orphan*/ ) ; 
 TYPE_1__* RCC ; 
 int /*<<< orphan*/  RCC_CFGR3_CECSW ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void RCC_CECCLKConfig(uint32_t RCC_CECCLK)
{ 
  /* Check the parameters */
  assert_param(IS_RCC_CECCLK(RCC_CECCLK));

  /* Clear CECSW bit */
  RCC->CFGR3 &= ~RCC_CFGR3_CECSW;
  /* Set CECSW bits according to RCC_CECCLK value */
  RCC->CFGR3 |= RCC_CECCLK;
}