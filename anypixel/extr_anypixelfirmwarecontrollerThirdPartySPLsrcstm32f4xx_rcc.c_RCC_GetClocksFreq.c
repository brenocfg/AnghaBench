#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int CFGR; int PLLCFGR; } ;
struct TYPE_4__ {int SYSCLK_Frequency; int HCLK_Frequency; int PCLK1_Frequency; int PCLK2_Frequency; } ;
typedef  TYPE_1__ RCC_ClocksTypeDef ;

/* Variables and functions */
 int* APBAHBPrescTable ; 
 int HSE_VALUE ; 
 int HSI_VALUE ; 
 TYPE_3__* RCC ; 
 int RCC_CFGR_HPRE ; 
 int RCC_CFGR_PPRE1 ; 
 int RCC_CFGR_PPRE2 ; 
 int RCC_CFGR_SWS ; 
 int RCC_PLLCFGR_PLLM ; 
 int RCC_PLLCFGR_PLLN ; 
 int RCC_PLLCFGR_PLLP ; 
 int RCC_PLLCFGR_PLLSRC ; 

void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks)
{
  uint32_t tmp = 0, presc = 0, pllvco = 0, pllp = 2, pllsource = 0, pllm = 2;

  /* Get SYSCLK source -------------------------------------------------------*/
  tmp = RCC->CFGR & RCC_CFGR_SWS;

  switch (tmp)
  {
    case 0x00:  /* HSI used as system clock source */
      RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
      break;
    case 0x04:  /* HSE used as system clock  source */
      RCC_Clocks->SYSCLK_Frequency = HSE_VALUE;
      break;
    case 0x08:  /* PLL used as system clock  source */

      /* PLL_VCO = (HSE_VALUE or HSI_VALUE / PLLM) * PLLN
         SYSCLK = PLL_VCO / PLLP
         */    
      pllsource = (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) >> 22;
      pllm = RCC->PLLCFGR & RCC_PLLCFGR_PLLM;
      
      if (pllsource != 0)
      {
        /* HSE used as PLL clock source */
        pllvco = (HSE_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
      }
      else
      {
        /* HSI used as PLL clock source */
        pllvco = (HSI_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);      
      }

      pllp = (((RCC->PLLCFGR & RCC_PLLCFGR_PLLP) >>16) + 1 ) *2;
      RCC_Clocks->SYSCLK_Frequency = pllvco/pllp;
      break;
    default:
      RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
      break;
  }
  /* Compute HCLK, PCLK1 and PCLK2 clocks frequencies ------------------------*/

  /* Get HCLK prescaler */
  tmp = RCC->CFGR & RCC_CFGR_HPRE;
  tmp = tmp >> 4;
  presc = APBAHBPrescTable[tmp];
  /* HCLK clock frequency */
  RCC_Clocks->HCLK_Frequency = RCC_Clocks->SYSCLK_Frequency >> presc;

  /* Get PCLK1 prescaler */
  tmp = RCC->CFGR & RCC_CFGR_PPRE1;
  tmp = tmp >> 10;
  presc = APBAHBPrescTable[tmp];
  /* PCLK1 clock frequency */
  RCC_Clocks->PCLK1_Frequency = RCC_Clocks->HCLK_Frequency >> presc;

  /* Get PCLK2 prescaler */
  tmp = RCC->CFGR & RCC_CFGR_PPRE2;
  tmp = tmp >> 13;
  presc = APBAHBPrescTable[tmp];
  /* PCLK2 clock frequency */
  RCC_Clocks->PCLK2_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
}