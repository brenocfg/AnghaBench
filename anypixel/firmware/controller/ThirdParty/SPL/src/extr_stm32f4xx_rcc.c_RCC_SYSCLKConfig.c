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
struct TYPE_2__ {int /*<<< orphan*/  CFGR; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_RCC_SYSCLK_SOURCE (int /*<<< orphan*/ ) ; 
 TYPE_1__* RCC ; 
 int /*<<< orphan*/  RCC_CFGR_SW ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RCC_SYSCLK_SOURCE(RCC_SYSCLKSource));

  tmpreg = RCC->CFGR;

  /* Clear SW[1:0] bits */
  tmpreg &= ~RCC_CFGR_SW;

  /* Set SW[1:0] bits according to RCC_SYSCLKSource value */
  tmpreg |= RCC_SYSCLKSource;

  /* Store the new value */
  RCC->CFGR = tmpreg;
}