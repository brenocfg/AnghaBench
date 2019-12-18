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
struct TYPE_2__ {int /*<<< orphan*/  BDCR; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_RCC_LSE (int /*<<< orphan*/ ) ; 
 TYPE_1__* RCC ; 
 int /*<<< orphan*/  RCC_BDCR_LSEBYP ; 
 int /*<<< orphan*/  RCC_BDCR_LSEON ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void RCC_LSEConfig(uint32_t RCC_LSE)
{
  /* Check the parameters */
  assert_param(IS_RCC_LSE(RCC_LSE));

  /* Reset LSEON and LSEBYP bits before configuring the LSE ------------------*/
  /* Reset LSEON bit */
  RCC->BDCR &= ~(RCC_BDCR_LSEON);

  /* Reset LSEBYP bit */
  RCC->BDCR &= ~(RCC_BDCR_LSEBYP);

  /* Configure LSE */
  RCC->BDCR |= RCC_LSE;
}