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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ CFGR1; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_SYSCFG_MEMORY_REMAP (scalar_t__) ; 
 TYPE_1__* SYSCFG ; 
 scalar_t__ SYSCFG_CFGR1_MEM_MODE ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void SYSCFG_MemoryRemapConfig(uint32_t SYSCFG_MemoryRemap)
{
  uint32_t tmpctrl = 0;

  /* Check the parameter */
  assert_param(IS_SYSCFG_MEMORY_REMAP(SYSCFG_MemoryRemap));

  /* Get CFGR1 register value */
  tmpctrl = SYSCFG->CFGR1;

  /* Clear MEM_MODE bits */
  tmpctrl &= (uint32_t) (~SYSCFG_CFGR1_MEM_MODE);

  /* Set the new MEM_MODE bits value */
  tmpctrl |= (uint32_t) SYSCFG_MemoryRemap;

  /* Set CFGR1 register with the new memory remap configuration */
  SYSCFG->CFGR1 = tmpctrl;
}