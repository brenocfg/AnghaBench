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
struct TYPE_2__ {int PLLCFGR; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_RCC_PLLM_VALUE (int) ; 
 int /*<<< orphan*/  IS_RCC_PLLN_VALUE (int) ; 
 int /*<<< orphan*/  IS_RCC_PLLP_VALUE (int) ; 
 int /*<<< orphan*/  IS_RCC_PLLQ_VALUE (int) ; 
 int /*<<< orphan*/  IS_RCC_PLL_SOURCE (int) ; 
 TYPE_1__* RCC ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void RCC_PLLConfig(uint32_t RCC_PLLSource, uint32_t PLLM, uint32_t PLLN, uint32_t PLLP, uint32_t PLLQ)
{
  /* Check the parameters */
  assert_param(IS_RCC_PLL_SOURCE(RCC_PLLSource));
  assert_param(IS_RCC_PLLM_VALUE(PLLM));
  assert_param(IS_RCC_PLLN_VALUE(PLLN));
  assert_param(IS_RCC_PLLP_VALUE(PLLP));
  assert_param(IS_RCC_PLLQ_VALUE(PLLQ));

  RCC->PLLCFGR = PLLM | (PLLN << 6) | (((PLLP >> 1) -1) << 16) | (RCC_PLLSource) |
                 (PLLQ << 24);
}