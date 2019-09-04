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
struct TYPE_2__ {scalar_t__ CFGR; } ;

/* Variables and functions */
 TYPE_1__* CRS ; 
 scalar_t__ CRS_CFGR_RELOAD ; 

void CRS_FrequencyErrorCounterReload(uint32_t CRS_ReloadValue)
{
 
  /* Clear RELOAD[15:0] bits */
  CRS->CFGR &= ~CRS_CFGR_RELOAD;
  
  /* Set the RELOAD[15:0] bits according to CRS_ReloadValue value */
  CRS->CFGR |= (uint32_t)CRS_ReloadValue;

}