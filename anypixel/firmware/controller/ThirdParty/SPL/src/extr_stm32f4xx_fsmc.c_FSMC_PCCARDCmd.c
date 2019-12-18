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
struct TYPE_2__ {int /*<<< orphan*/  PCR4; } ;
typedef  scalar_t__ FunctionalState ;

/* Variables and functions */
 scalar_t__ DISABLE ; 
 TYPE_1__* FSMC_Bank4 ; 
 int /*<<< orphan*/  IS_FUNCTIONAL_STATE (scalar_t__) ; 
 int /*<<< orphan*/  PCR_PBKEN_RESET ; 
 int /*<<< orphan*/  PCR_PBKEN_SET ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void FSMC_PCCARDCmd(FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the PCCARD Bank by setting the PBKEN bit in the PCR4 register */
    FSMC_Bank4->PCR4 |= PCR_PBKEN_SET;
  }
  else
  {
    /* Disable the PCCARD Bank by clearing the PBKEN bit in the PCR4 register */
    FSMC_Bank4->PCR4 &= PCR_PBKEN_RESET;
  }
}