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
 int /*<<< orphan*/  IS_RCC_PLL_MUL (int) ; 
 int /*<<< orphan*/  IS_RCC_PLL_SOURCE (int) ; 
 TYPE_1__* RCC ; 
 int RCC_CFGR_PLLMULL ; 
 int RCC_CFGR_PLLSRC ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void RCC_PLLConfig(uint32_t RCC_PLLSource, uint32_t RCC_PLLMul)
{
  /* Check the parameters */
  assert_param(IS_RCC_PLL_SOURCE(RCC_PLLSource));
  assert_param(IS_RCC_PLL_MUL(RCC_PLLMul));

  /* Clear PLL Source [16] and Multiplier [21:18] bits */
  RCC->CFGR &= ~(RCC_CFGR_PLLMULL | RCC_CFGR_PLLSRC);

  /* Set the PLL Source and Multiplier */
  RCC->CFGR |= (uint32_t)(RCC_PLLSource | RCC_PLLMul);
}