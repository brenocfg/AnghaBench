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
typedef  int uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  CR; } ;
struct TYPE_3__ {int USER; } ;
typedef  scalar_t__ FLASH_Status ;

/* Variables and functions */
 TYPE_2__* FLASH ; 
 scalar_t__ FLASH_COMPLETE ; 
 int /*<<< orphan*/  FLASH_CR_OPTPG ; 
 int /*<<< orphan*/  FLASH_ER_PRG_TIMEOUT ; 
 scalar_t__ FLASH_TIMEOUT ; 
 scalar_t__ FLASH_WaitForLastOperation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_OB_BOOT0 (int) ; 
 TYPE_1__* OB ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

FLASH_Status FLASH_OB_BOOT0Config(uint8_t OB_BOOT0)
{
  FLASH_Status status = FLASH_COMPLETE; 

  /* Check the parameters */
  assert_param(IS_OB_BOOT0(OB_BOOT0));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
  
  if(status == FLASH_COMPLETE)
  {  
    /* Enable the Option Bytes Programming operation */
    FLASH->CR |= FLASH_CR_OPTPG;

    OB->USER = OB_BOOT0 | 0xF7;
  
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status != FLASH_TIMEOUT)
    {
      /* If the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= ~FLASH_CR_OPTPG;
    }
  }
  /* Return the Option Byte program Status */
  return status;
}