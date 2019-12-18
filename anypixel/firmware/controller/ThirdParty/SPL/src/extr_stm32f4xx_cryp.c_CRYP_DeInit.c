#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  DISABLE ; 
 int /*<<< orphan*/  ENABLE ; 
 int /*<<< orphan*/  RCC_AHB2PeriphResetCmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCC_AHB2Periph_CRYP ; 

void CRYP_DeInit(void)
{
  /* Enable CRYP reset state */
  RCC_AHB2PeriphResetCmd(RCC_AHB2Periph_CRYP, ENABLE);

  /* Release CRYP from reset state */
  RCC_AHB2PeriphResetCmd(RCC_AHB2Periph_CRYP, DISABLE);
}