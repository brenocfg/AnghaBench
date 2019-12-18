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
typedef  int uint32_t ;
struct TYPE_2__ {int CFGR2; } ;
typedef  scalar_t__ FlagStatus ;

/* Variables and functions */
 int /*<<< orphan*/  IS_SYSCFG_FLAG (int) ; 
 scalar_t__ RESET ; 
 scalar_t__ SET ; 
 TYPE_1__* SYSCFG ; 
 int SYSCFG_CFGR2_SRAM_PE ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

FlagStatus SYSCFG_GetFlagStatus(uint32_t SYSCFG_Flag)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameter */
  assert_param(IS_SYSCFG_FLAG(SYSCFG_Flag));

  /* Check the status of the specified SPI flag */
  if ((SYSCFG->CFGR2 & SYSCFG_CFGR2_SRAM_PE) != (uint32_t)RESET)
  {
    /* SYSCFG_Flag is set */
    bitstatus = SET;
  }
  else
  {
    /* SYSCFG_Flag is reset */
    bitstatus = RESET;
  }
  /* Return the SYSCFG_Flag status */
  return  bitstatus;
}