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
typedef  size_t uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/ * BTCR; } ;
typedef  scalar_t__ FunctionalState ;

/* Variables and functions */
 int /*<<< orphan*/  BCR_MBKEN_RESET ; 
 int /*<<< orphan*/  BCR_MBKEN_SET ; 
 scalar_t__ DISABLE ; 
 TYPE_1__* FSMC_Bank1 ; 
 int /*<<< orphan*/  IS_FSMC_NORSRAM_BANK (size_t) ; 
 int /*<<< orphan*/  IS_FUNCTIONAL_STATE (scalar_t__) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void FSMC_NORSRAMCmd(uint32_t FSMC_Bank, FunctionalState NewState)
{
  assert_param(IS_FSMC_NORSRAM_BANK(FSMC_Bank));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the selected NOR/SRAM Bank by setting the PBKEN bit in the BCRx register */
    FSMC_Bank1->BTCR[FSMC_Bank] |= BCR_MBKEN_SET;
  }
  else
  {
    /* Disable the selected NOR/SRAM Bank by clearing the PBKEN bit in the BCRx register */
    FSMC_Bank1->BTCR[FSMC_Bank] &= BCR_MBKEN_RESET;
  }
}