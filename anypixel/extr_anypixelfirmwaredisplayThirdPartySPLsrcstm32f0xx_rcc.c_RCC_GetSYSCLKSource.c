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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int CFGR; } ;

/* Variables and functions */
 TYPE_1__* RCC ; 
 int RCC_CFGR_SWS ; 

uint8_t RCC_GetSYSCLKSource(void)
{
  return ((uint8_t)(RCC->CFGR & RCC_CFGR_SWS));
}