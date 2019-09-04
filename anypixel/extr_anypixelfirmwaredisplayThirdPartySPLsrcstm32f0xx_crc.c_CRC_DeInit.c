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
struct TYPE_2__ {int DR; int POL; int IDR; int INIT; int /*<<< orphan*/  CR; } ;

/* Variables and functions */
 TYPE_1__* CRC ; 
 int /*<<< orphan*/  CRC_CR_RESET ; 

void CRC_DeInit(void)
{
  /* Set DR register to reset value */
  CRC->DR = 0xFFFFFFFF;
  
  /* Set the POL register to the reset value: 0x04C11DB7 */
  CRC->POL = 0x04C11DB7;
  
  /* Reset IDR register */
  CRC->IDR = 0x00;
  
  /* Set INIT register to reset value */
  CRC->INIT = 0xFFFFFFFF;
  
  /* Reset the CRC calculation unit */
  CRC->CR = CRC_CR_RESET;
}