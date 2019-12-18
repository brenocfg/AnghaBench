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
struct TYPE_5__ {int CLKCR; } ;
struct TYPE_4__ {int SDIO_ClockEdge; int SDIO_ClockBypass; int SDIO_ClockPowerSave; int SDIO_BusWide; int SDIO_HardwareFlowControl; int SDIO_ClockDiv; } ;
typedef  TYPE_1__ SDIO_InitTypeDef ;

/* Variables and functions */
 int CLKCR_CLEAR_MASK ; 
 int /*<<< orphan*/  IS_SDIO_BUS_WIDE (int) ; 
 int /*<<< orphan*/  IS_SDIO_CLOCK_BYPASS (int) ; 
 int /*<<< orphan*/  IS_SDIO_CLOCK_EDGE (int) ; 
 int /*<<< orphan*/  IS_SDIO_CLOCK_POWER_SAVE (int) ; 
 int /*<<< orphan*/  IS_SDIO_HARDWARE_FLOW_CONTROL (int) ; 
 TYPE_3__* SDIO ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void SDIO_Init(SDIO_InitTypeDef* SDIO_InitStruct)
{
  uint32_t tmpreg = 0;
    
  /* Check the parameters */
  assert_param(IS_SDIO_CLOCK_EDGE(SDIO_InitStruct->SDIO_ClockEdge));
  assert_param(IS_SDIO_CLOCK_BYPASS(SDIO_InitStruct->SDIO_ClockBypass));
  assert_param(IS_SDIO_CLOCK_POWER_SAVE(SDIO_InitStruct->SDIO_ClockPowerSave));
  assert_param(IS_SDIO_BUS_WIDE(SDIO_InitStruct->SDIO_BusWide));
  assert_param(IS_SDIO_HARDWARE_FLOW_CONTROL(SDIO_InitStruct->SDIO_HardwareFlowControl)); 
   
/*---------------------------- SDIO CLKCR Configuration ------------------------*/  
  /* Get the SDIO CLKCR value */
  tmpreg = SDIO->CLKCR;
  
  /* Clear CLKDIV, PWRSAV, BYPASS, WIDBUS, NEGEDGE, HWFC_EN bits */
  tmpreg &= CLKCR_CLEAR_MASK;
  
  /* Set CLKDIV bits according to SDIO_ClockDiv value */
  /* Set PWRSAV bit according to SDIO_ClockPowerSave value */
  /* Set BYPASS bit according to SDIO_ClockBypass value */
  /* Set WIDBUS bits according to SDIO_BusWide value */
  /* Set NEGEDGE bits according to SDIO_ClockEdge value */
  /* Set HWFC_EN bits according to SDIO_HardwareFlowControl value */
  tmpreg |= (SDIO_InitStruct->SDIO_ClockDiv  | SDIO_InitStruct->SDIO_ClockPowerSave |
             SDIO_InitStruct->SDIO_ClockBypass | SDIO_InitStruct->SDIO_BusWide |
             SDIO_InitStruct->SDIO_ClockEdge | SDIO_InitStruct->SDIO_HardwareFlowControl); 
  
  /* Write to SDIO CLKCR */
  SDIO->CLKCR = tmpreg;
}