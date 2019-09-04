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
struct TYPE_2__ {int OPTCR; int /*<<< orphan*/  OPTKEYR; } ;

/* Variables and functions */
 TYPE_1__* FLASH ; 
 int FLASH_OPTCR_OPTLOCK ; 
 int /*<<< orphan*/  FLASH_OPT_KEY1 ; 
 int /*<<< orphan*/  FLASH_OPT_KEY2 ; 
 int RESET ; 

void FLASH_OB_Unlock(void)
{
  if((FLASH->OPTCR & FLASH_OPTCR_OPTLOCK) != RESET)
  {
    /* Authorizes the Option Byte register programming */
    FLASH->OPTKEYR = FLASH_OPT_KEY1;
    FLASH->OPTKEYR = FLASH_OPT_KEY2;
  }  
}