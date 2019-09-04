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
struct TYPE_2__ {int CR; int /*<<< orphan*/  KEYR; } ;

/* Variables and functions */
 TYPE_1__* FLASH ; 
 int FLASH_CR_LOCK ; 
 int /*<<< orphan*/  FLASH_FKEY1 ; 
 int /*<<< orphan*/  FLASH_FKEY2 ; 
 int RESET ; 

void FLASH_Unlock(void)
{
  if((FLASH->CR & FLASH_CR_LOCK) != RESET)
  {
    /* Unlocking the program memory access */
    FLASH->KEYR = FLASH_FKEY1;
    FLASH->KEYR = FLASH_FKEY2;
  }
}