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
struct TYPE_2__ {scalar_t__ ACR; } ;

/* Variables and functions */
 TYPE_1__* FLASH ; 
 scalar_t__ FLASH_ACR_LATENCY ; 
 int /*<<< orphan*/  IS_FLASH_LATENCY (scalar_t__) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void FLASH_SetLatency(uint32_t FLASH_Latency)
{
   uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_FLASH_LATENCY(FLASH_Latency));

  /* Read the ACR register */
  tmpreg = FLASH->ACR;  

  /* Sets the Latency value */
  tmpreg &= (uint32_t) (~((uint32_t)FLASH_ACR_LATENCY));
  tmpreg |= FLASH_Latency;

  /* Write the ACR register */
  FLASH->ACR = tmpreg;
}