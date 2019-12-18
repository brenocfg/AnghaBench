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
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  CR; } ;
struct TYPE_3__ {int RDP; } ;
typedef  scalar_t__ FLASH_Status ;

/* Variables and functions */
 TYPE_2__* FLASH ; 
 scalar_t__ FLASH_COMPLETE ; 
 int /*<<< orphan*/  FLASH_CR_OPTER ; 
 int /*<<< orphan*/  FLASH_CR_OPTPG ; 
 int /*<<< orphan*/  FLASH_CR_STRT ; 
 int /*<<< orphan*/  FLASH_ER_PRG_TIMEOUT ; 
 scalar_t__ FLASH_OB_GetRDP () ; 
 scalar_t__ FLASH_TIMEOUT ; 
 scalar_t__ FLASH_WaitForLastOperation (int /*<<< orphan*/ ) ; 
 TYPE_1__* OB ; 
 int OB_RDP_Level_0 ; 
 scalar_t__ RESET ; 

FLASH_Status FLASH_OB_Erase(void)
{
  uint16_t rdptmp = OB_RDP_Level_0;

  FLASH_Status status = FLASH_COMPLETE;

  /* Get the actual read protection Option Byte value */ 
  if(FLASH_OB_GetRDP() != RESET)
  {
    rdptmp = 0x00;  
  }

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

  if(status == FLASH_COMPLETE)
  {   
    /* If the previous operation is completed, proceed to erase the option bytes */
    FLASH->CR |= FLASH_CR_OPTER;
    FLASH->CR |= FLASH_CR_STRT;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    
    if(status == FLASH_COMPLETE)
    {
      /* If the erase operation is completed, disable the OPTER Bit */
      FLASH->CR &= ~FLASH_CR_OPTER;
       
      /* Enable the Option Bytes Programming operation */
      FLASH->CR |= FLASH_CR_OPTPG;

      /* Restore the last read protection Option Byte value */
      OB->RDP = (uint16_t)rdptmp; 

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
 
      if(status != FLASH_TIMEOUT)
      {
        /* if the program operation is completed, disable the OPTPG Bit */
        FLASH->CR &= ~FLASH_CR_OPTPG;
      }
    }
    else
    {
      if (status != FLASH_TIMEOUT)
      {
        /* Disable the OPTPG Bit */
        FLASH->CR &= ~FLASH_CR_OPTPG;
      }
    }  
  }
  /* Return the erase status */
  return status;
}