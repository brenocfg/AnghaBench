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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  CR; } ;
struct TYPE_3__ {int WRP0; int WRP1; int WRP2; int WRP3; } ;
typedef  scalar_t__ FLASH_Status ;

/* Variables and functions */
 TYPE_2__* FLASH ; 
 scalar_t__ FLASH_COMPLETE ; 
 int /*<<< orphan*/  FLASH_CR_OPTPG ; 
 int /*<<< orphan*/  FLASH_ER_PRG_TIMEOUT ; 
 scalar_t__ FLASH_TIMEOUT ; 
 scalar_t__ FLASH_WaitForLastOperation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_OB_WRP (int) ; 
 TYPE_1__* OB ; 
 int OB_WRP0_WRP0 ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

FLASH_Status FLASH_OB_EnableWRP(uint32_t OB_WRP)
{
 uint16_t WRP0_Data = 0xFFFF, WRP1_Data = 0xFFFF, WRP2_Data = 0xFFFF, WRP3_Data = 0xFFFF;

  FLASH_Status status = FLASH_COMPLETE;

  /* Check the parameters */
  assert_param(IS_OB_WRP(OB_WRP));

  OB_WRP = (uint32_t)(~OB_WRP);
  WRP0_Data = (uint16_t)(OB_WRP & OB_WRP0_WRP0);
  WRP1_Data = (uint16_t)((OB_WRP >> 8) & OB_WRP0_WRP0);
  WRP2_Data = (uint16_t)((OB_WRP >> 16) & OB_WRP0_WRP0) ;
  WRP3_Data = (uint16_t)((OB_WRP >> 24) & OB_WRP0_WRP0) ;
    
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

  if(status == FLASH_COMPLETE)
  {
    FLASH->CR |= FLASH_CR_OPTPG;

    if(WRP0_Data != 0xFF)
    {
      OB->WRP0 = WRP0_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    }
    if((status == FLASH_COMPLETE) && (WRP1_Data != 0xFF))
    {
      OB->WRP1 = WRP1_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    }
    if((status == FLASH_COMPLETE) && (WRP2_Data != 0xFF))
    {
      OB->WRP2 = WRP2_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    }    
    if((status == FLASH_COMPLETE) && (WRP3_Data != 0xFF))
    {
      OB->WRP3 = WRP3_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    }  
    if(status != FLASH_TIMEOUT)
    {
      /* if the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= ~FLASH_CR_OPTPG;
    }
  } 
  /* Return the write protection operation Status */
  return status;
}