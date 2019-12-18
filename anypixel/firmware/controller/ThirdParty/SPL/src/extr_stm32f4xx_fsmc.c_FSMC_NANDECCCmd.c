#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  PCR2; } ;
struct TYPE_3__ {int /*<<< orphan*/  PCR3; } ;
typedef  scalar_t__ FunctionalState ;

/* Variables and functions */
 scalar_t__ DISABLE ; 
 TYPE_2__* FSMC_Bank2 ; 
 scalar_t__ FSMC_Bank2_NAND ; 
 TYPE_1__* FSMC_Bank3 ; 
 int /*<<< orphan*/  IS_FSMC_NAND_BANK (scalar_t__) ; 
 int /*<<< orphan*/  IS_FUNCTIONAL_STATE (scalar_t__) ; 
 int /*<<< orphan*/  PCR_ECCEN_RESET ; 
 int /*<<< orphan*/  PCR_ECCEN_SET ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void FSMC_NANDECCCmd(uint32_t FSMC_Bank, FunctionalState NewState)
{
  assert_param(IS_FSMC_NAND_BANK(FSMC_Bank));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the selected NAND Bank ECC function by setting the ECCEN bit in the PCRx register */
    if(FSMC_Bank == FSMC_Bank2_NAND)
    {
      FSMC_Bank2->PCR2 |= PCR_ECCEN_SET;
    }
    else
    {
      FSMC_Bank3->PCR3 |= PCR_ECCEN_SET;
    }
  }
  else
  {
    /* Disable the selected NAND Bank ECC function by clearing the ECCEN bit in the PCRx register */
    if(FSMC_Bank == FSMC_Bank2_NAND)
    {
      FSMC_Bank2->PCR2 &= PCR_ECCEN_RESET;
    }
    else
    {
      FSMC_Bank3->PCR3 &= PCR_ECCEN_RESET;
    }
  }
}