#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_11__ {int PCR2; int PMEM2; int PATT2; } ;
struct TYPE_10__ {int PCR3; int PMEM3; int PATT3; } ;
struct TYPE_9__ {scalar_t__ FSMC_Bank; int FSMC_MemoryDataWidth; int FSMC_ECC; int FSMC_ECCPageSize; int FSMC_TCLRSetupTime; int FSMC_TARSetupTime; TYPE_2__* FSMC_AttributeSpaceTimingStruct; TYPE_1__* FSMC_CommonSpaceTimingStruct; scalar_t__ FSMC_Waitfeature; } ;
struct TYPE_8__ {int FSMC_WaitSetupTime; int FSMC_HoldSetupTime; int FSMC_HiZSetupTime; scalar_t__ FSMC_SetupTime; } ;
struct TYPE_7__ {int FSMC_WaitSetupTime; int FSMC_HoldSetupTime; int FSMC_HiZSetupTime; scalar_t__ FSMC_SetupTime; } ;
typedef  TYPE_3__ FSMC_NANDInitTypeDef ;

/* Variables and functions */
 TYPE_6__* FSMC_Bank2 ; 
 scalar_t__ FSMC_Bank2_NAND ; 
 TYPE_5__* FSMC_Bank3 ; 
 int /*<<< orphan*/  IS_FSMC_ECCPAGE_SIZE (int) ; 
 int /*<<< orphan*/  IS_FSMC_ECC_STATE (int) ; 
 int /*<<< orphan*/  IS_FSMC_HIZ_TIME (int) ; 
 int /*<<< orphan*/  IS_FSMC_HOLD_TIME (int) ; 
 int /*<<< orphan*/  IS_FSMC_MEMORY_WIDTH (int) ; 
 int /*<<< orphan*/  IS_FSMC_NAND_BANK (scalar_t__) ; 
 int /*<<< orphan*/  IS_FSMC_SETUP_TIME (scalar_t__) ; 
 int /*<<< orphan*/  IS_FSMC_TAR_TIME (int) ; 
 int /*<<< orphan*/  IS_FSMC_TCLR_TIME (int) ; 
 int /*<<< orphan*/  IS_FSMC_WAIT_FEATURE (scalar_t__) ; 
 int /*<<< orphan*/  IS_FSMC_WAIT_TIME (int) ; 
 int PCR_MEMORYTYPE_NAND ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void FSMC_NANDInit(FSMC_NANDInitTypeDef* FSMC_NANDInitStruct)
{
  uint32_t tmppcr = 0x00000000, tmppmem = 0x00000000, tmppatt = 0x00000000; 
    
  /* Check the parameters */
  assert_param( IS_FSMC_NAND_BANK(FSMC_NANDInitStruct->FSMC_Bank));
  assert_param( IS_FSMC_WAIT_FEATURE(FSMC_NANDInitStruct->FSMC_Waitfeature));
  assert_param( IS_FSMC_MEMORY_WIDTH(FSMC_NANDInitStruct->FSMC_MemoryDataWidth));
  assert_param( IS_FSMC_ECC_STATE(FSMC_NANDInitStruct->FSMC_ECC));
  assert_param( IS_FSMC_ECCPAGE_SIZE(FSMC_NANDInitStruct->FSMC_ECCPageSize));
  assert_param( IS_FSMC_TCLR_TIME(FSMC_NANDInitStruct->FSMC_TCLRSetupTime));
  assert_param( IS_FSMC_TAR_TIME(FSMC_NANDInitStruct->FSMC_TARSetupTime));
  assert_param(IS_FSMC_SETUP_TIME(FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_SetupTime));
  assert_param(IS_FSMC_WAIT_TIME(FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_WaitSetupTime));
  assert_param(IS_FSMC_HOLD_TIME(FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HoldSetupTime));
  assert_param(IS_FSMC_HIZ_TIME(FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HiZSetupTime));
  assert_param(IS_FSMC_SETUP_TIME(FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_SetupTime));
  assert_param(IS_FSMC_WAIT_TIME(FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_WaitSetupTime));
  assert_param(IS_FSMC_HOLD_TIME(FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HoldSetupTime));
  assert_param(IS_FSMC_HIZ_TIME(FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HiZSetupTime));
  
  /* Set the tmppcr value according to FSMC_NANDInitStruct parameters */
  tmppcr = (uint32_t)FSMC_NANDInitStruct->FSMC_Waitfeature |
            PCR_MEMORYTYPE_NAND |
            FSMC_NANDInitStruct->FSMC_MemoryDataWidth |
            FSMC_NANDInitStruct->FSMC_ECC |
            FSMC_NANDInitStruct->FSMC_ECCPageSize |
            (FSMC_NANDInitStruct->FSMC_TCLRSetupTime << 9 )|
            (FSMC_NANDInitStruct->FSMC_TARSetupTime << 13);
            
  /* Set tmppmem value according to FSMC_CommonSpaceTimingStructure parameters */
  tmppmem = (uint32_t)FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_SetupTime |
            (FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_WaitSetupTime << 8) |
            (FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HoldSetupTime << 16)|
            (FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HiZSetupTime << 24); 
            
  /* Set tmppatt value according to FSMC_AttributeSpaceTimingStructure parameters */
  tmppatt = (uint32_t)FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_SetupTime |
            (FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_WaitSetupTime << 8) |
            (FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HoldSetupTime << 16)|
            (FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HiZSetupTime << 24);
  
  if(FSMC_NANDInitStruct->FSMC_Bank == FSMC_Bank2_NAND)
  {
    /* FSMC_Bank2_NAND registers configuration */
    FSMC_Bank2->PCR2 = tmppcr;
    FSMC_Bank2->PMEM2 = tmppmem;
    FSMC_Bank2->PATT2 = tmppatt;
  }
  else
  {
    /* FSMC_Bank3_NAND registers configuration */
    FSMC_Bank3->PCR3 = tmppcr;
    FSMC_Bank3->PMEM3 = tmppmem;
    FSMC_Bank3->PATT3 = tmppatt;
  }
}