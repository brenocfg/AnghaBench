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
struct TYPE_2__ {int CFGR; } ;

/* Variables and functions */
 int CFGR_MCO2_RESET_MASK ; 
 int /*<<< orphan*/  IS_RCC_MCO2DIV (int) ; 
 int /*<<< orphan*/  IS_RCC_MCO2SOURCE (int) ; 
 TYPE_1__* RCC ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void RCC_MCO2Config(uint32_t RCC_MCO2Source, uint32_t RCC_MCO2Div)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_MCO2SOURCE(RCC_MCO2Source));
  assert_param(IS_RCC_MCO2DIV(RCC_MCO2Div));
  
  tmpreg = RCC->CFGR;
  
  /* Clear MCO2 and MCO2PRE[2:0] bits */
  tmpreg &= CFGR_MCO2_RESET_MASK;

  /* Select MCO2 clock source and prescaler */
  tmpreg |= RCC_MCO2Source | RCC_MCO2Div;

  /* Store the new value */
  RCC->CFGR = tmpreg;  
}