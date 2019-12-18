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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  CR; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_PLS_MASK ; 
 int /*<<< orphan*/  IS_PWR_PVD_LEVEL (int /*<<< orphan*/ ) ; 
 TYPE_1__* PWR ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_PWR_PVD_LEVEL(PWR_PVDLevel));
  
  tmpreg = PWR->CR;
  
  /* Clear PLS[7:5] bits */
  tmpreg &= CR_PLS_MASK;
  
  /* Set PLS[7:5] bits according to PWR_PVDLevel value */
  tmpreg |= PWR_PVDLevel;
  
  /* Store the new value */
  PWR->CR = tmpreg;
}