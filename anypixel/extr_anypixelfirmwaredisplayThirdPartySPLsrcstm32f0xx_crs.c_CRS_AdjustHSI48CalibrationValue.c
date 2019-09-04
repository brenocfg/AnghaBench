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
typedef  int uint32_t ;
struct TYPE_2__ {int CR; } ;

/* Variables and functions */
 TYPE_1__* CRS ; 
 int CRS_CR_TRIM ; 

void CRS_AdjustHSI48CalibrationValue(uint8_t CRS_HSI48CalibrationValue)
{
  /* Clear TRIM[5:0] bits */
  CRS->CR &= ~CRS_CR_TRIM;
  
  /* Set the TRIM[5:0] bits according to CRS_HSI48CalibrationValue value */
  CRS->CR |= (uint32_t)((uint32_t)CRS_HSI48CalibrationValue << 8);

}