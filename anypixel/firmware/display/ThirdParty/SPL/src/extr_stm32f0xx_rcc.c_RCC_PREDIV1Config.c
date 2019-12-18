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
struct TYPE_2__ {int /*<<< orphan*/  CFGR2; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_RCC_PREDIV1 (int /*<<< orphan*/ ) ; 
 TYPE_1__* RCC ; 
 int /*<<< orphan*/  RCC_CFGR2_PREDIV1 ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void RCC_PREDIV1Config(uint32_t RCC_PREDIV1_Div)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_PREDIV1(RCC_PREDIV1_Div));

  tmpreg = RCC->CFGR2;
  /* Clear PREDIV1[3:0] bits */
  tmpreg &= ~(RCC_CFGR2_PREDIV1);
  /* Set the PREDIV1 division factor */
  tmpreg |= RCC_PREDIV1_Div;
  /* Store the new value */
  RCC->CFGR2 = tmpreg;
}