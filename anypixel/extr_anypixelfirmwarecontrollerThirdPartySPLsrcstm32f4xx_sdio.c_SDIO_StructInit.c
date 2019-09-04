#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int SDIO_ClockDiv; int /*<<< orphan*/  SDIO_HardwareFlowControl; int /*<<< orphan*/  SDIO_BusWide; int /*<<< orphan*/  SDIO_ClockPowerSave; int /*<<< orphan*/  SDIO_ClockBypass; int /*<<< orphan*/  SDIO_ClockEdge; } ;
typedef  TYPE_1__ SDIO_InitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  SDIO_BusWide_1b ; 
 int /*<<< orphan*/  SDIO_ClockBypass_Disable ; 
 int /*<<< orphan*/  SDIO_ClockEdge_Rising ; 
 int /*<<< orphan*/  SDIO_ClockPowerSave_Disable ; 
 int /*<<< orphan*/  SDIO_HardwareFlowControl_Disable ; 

void SDIO_StructInit(SDIO_InitTypeDef* SDIO_InitStruct)
{
  /* SDIO_InitStruct members default value */
  SDIO_InitStruct->SDIO_ClockDiv = 0x00;
  SDIO_InitStruct->SDIO_ClockEdge = SDIO_ClockEdge_Rising;
  SDIO_InitStruct->SDIO_ClockBypass = SDIO_ClockBypass_Disable;
  SDIO_InitStruct->SDIO_ClockPowerSave = SDIO_ClockPowerSave_Disable;
  SDIO_InitStruct->SDIO_BusWide = SDIO_BusWide_1b;
  SDIO_InitStruct->SDIO_HardwareFlowControl = SDIO_HardwareFlowControl_Disable;
}