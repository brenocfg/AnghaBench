#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {scalar_t__ SR2; } ;
struct TYPE_5__ {scalar_t__ SR3; } ;
struct TYPE_4__ {scalar_t__ SR4; } ;
typedef  scalar_t__ ITStatus ;

/* Variables and functions */
 TYPE_3__* FSMC_Bank2 ; 
 scalar_t__ FSMC_Bank2_NAND ; 
 TYPE_2__* FSMC_Bank3 ; 
 scalar_t__ FSMC_Bank3_NAND ; 
 TYPE_1__* FSMC_Bank4 ; 
 int /*<<< orphan*/  IS_FSMC_GET_IT (scalar_t__) ; 
 int /*<<< orphan*/  IS_FSMC_IT_BANK (scalar_t__) ; 
 scalar_t__ RESET ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

ITStatus FSMC_GetITStatus(uint32_t FSMC_Bank, uint32_t FSMC_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t tmpsr = 0x0, itstatus = 0x0, itenable = 0x0; 
  
  /* Check the parameters */
  assert_param(IS_FSMC_IT_BANK(FSMC_Bank));
  assert_param(IS_FSMC_GET_IT(FSMC_IT));
  
  if(FSMC_Bank == FSMC_Bank2_NAND)
  {
    tmpsr = FSMC_Bank2->SR2;
  }  
  else if(FSMC_Bank == FSMC_Bank3_NAND)
  {
    tmpsr = FSMC_Bank3->SR3;
  }
  /* FSMC_Bank4_PCCARD*/
  else
  {
    tmpsr = FSMC_Bank4->SR4;
  } 
  
  itstatus = tmpsr & FSMC_IT;
  
  itenable = tmpsr & (FSMC_IT >> 3);
  if ((itstatus != (uint32_t)RESET)  && (itenable != (uint32_t)RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus; 
}