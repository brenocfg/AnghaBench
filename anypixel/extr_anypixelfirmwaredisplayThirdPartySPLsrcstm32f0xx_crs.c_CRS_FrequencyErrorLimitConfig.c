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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  CFGR; } ;

/* Variables and functions */
 TYPE_1__* CRS ; 
 int /*<<< orphan*/  CRS_CFGR_FELIM ; 

void CRS_FrequencyErrorLimitConfig(uint8_t CRS_ErrorLimitValue)
{
  /* Clear FELIM[7:0] bits */
  CRS->CFGR &= ~CRS_CFGR_FELIM;
  
  /* Set the FELIM[7:0] bits according to CRS_ErrorLimitValue value */
  CRS->CFGR |= (uint32_t)CRS_ErrorLimitValue;
}