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
struct TYPE_2__ {int PCR4; int SR4; int PMEM4; int PATT4; int PIO4; } ;

/* Variables and functions */
 TYPE_1__* FSMC_Bank4 ; 

void FSMC_PCCARDDeInit(void)
{
  /* Set the FSMC_Bank4 registers to their reset values */
  FSMC_Bank4->PCR4 = 0x00000018; 
  FSMC_Bank4->SR4 = 0x00000000;	
  FSMC_Bank4->PMEM4 = 0xFCFCFCFC;
  FSMC_Bank4->PATT4 = 0xFCFCFCFC;
  FSMC_Bank4->PIO4 = 0xFCFCFCFC;
}