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
struct TYPE_3__ {int SDIO_Argument; int SDIO_CmdIndex; int /*<<< orphan*/  SDIO_CPSM; int /*<<< orphan*/  SDIO_Wait; int /*<<< orphan*/  SDIO_Response; } ;
typedef  TYPE_1__ SDIO_CmdInitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  SDIO_CPSM_Disable ; 
 int /*<<< orphan*/  SDIO_Response_No ; 
 int /*<<< orphan*/  SDIO_Wait_No ; 

void SDIO_CmdStructInit(SDIO_CmdInitTypeDef* SDIO_CmdInitStruct)
{
  /* SDIO_CmdInitStruct members default value */
  SDIO_CmdInitStruct->SDIO_Argument = 0x00;
  SDIO_CmdInitStruct->SDIO_CmdIndex = 0x00;
  SDIO_CmdInitStruct->SDIO_Response = SDIO_Response_No;
  SDIO_CmdInitStruct->SDIO_Wait = SDIO_Wait_No;
  SDIO_CmdInitStruct->SDIO_CPSM = SDIO_CPSM_Disable;
}