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
typedef  size_t uint32_t ;
struct TYPE_4__ {int* BTCR; } ;
struct TYPE_3__ {int* BWTR; } ;

/* Variables and functions */
 TYPE_2__* FSMC_Bank1 ; 
 TYPE_1__* FSMC_Bank1E ; 
 size_t FSMC_Bank1_NORSRAM1 ; 
 int /*<<< orphan*/  IS_FSMC_NORSRAM_BANK (size_t) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void FSMC_NORSRAMDeInit(uint32_t FSMC_Bank)
{
  /* Check the parameter */
  assert_param(IS_FSMC_NORSRAM_BANK(FSMC_Bank));
  
  /* FSMC_Bank1_NORSRAM1 */
  if(FSMC_Bank == FSMC_Bank1_NORSRAM1)
  {
    FSMC_Bank1->BTCR[FSMC_Bank] = 0x000030DB;    
  }
  /* FSMC_Bank1_NORSRAM2,  FSMC_Bank1_NORSRAM3 or FSMC_Bank1_NORSRAM4 */
  else
  {   
    FSMC_Bank1->BTCR[FSMC_Bank] = 0x000030D2; 
  }
  FSMC_Bank1->BTCR[FSMC_Bank + 1] = 0x0FFFFFFF;
  FSMC_Bank1E->BWTR[FSMC_Bank] = 0x0FFFFFFF;  
}