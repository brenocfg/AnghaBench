#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int CMD; int /*<<< orphan*/  ARG; } ;
struct TYPE_4__ {int SDIO_Response; int SDIO_Wait; int SDIO_CPSM; scalar_t__ SDIO_CmdIndex; int /*<<< orphan*/  SDIO_Argument; } ;
typedef  TYPE_1__ SDIO_CmdInitTypeDef ;

/* Variables and functions */
 int CMD_CLEAR_MASK ; 
 int /*<<< orphan*/  IS_SDIO_CMD_INDEX (scalar_t__) ; 
 int /*<<< orphan*/  IS_SDIO_CPSM (int) ; 
 int /*<<< orphan*/  IS_SDIO_RESPONSE (int) ; 
 int /*<<< orphan*/  IS_SDIO_WAIT (int) ; 
 TYPE_3__* SDIO ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void SDIO_SendCommand(SDIO_CmdInitTypeDef *SDIO_CmdInitStruct)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_SDIO_CMD_INDEX(SDIO_CmdInitStruct->SDIO_CmdIndex));
  assert_param(IS_SDIO_RESPONSE(SDIO_CmdInitStruct->SDIO_Response));
  assert_param(IS_SDIO_WAIT(SDIO_CmdInitStruct->SDIO_Wait));
  assert_param(IS_SDIO_CPSM(SDIO_CmdInitStruct->SDIO_CPSM));
  
/*---------------------------- SDIO ARG Configuration ------------------------*/
  /* Set the SDIO Argument value */
  SDIO->ARG = SDIO_CmdInitStruct->SDIO_Argument;
  
/*---------------------------- SDIO CMD Configuration ------------------------*/  
  /* Get the SDIO CMD value */
  tmpreg = SDIO->CMD;
  /* Clear CMDINDEX, WAITRESP, WAITINT, WAITPEND, CPSMEN bits */
  tmpreg &= CMD_CLEAR_MASK;
  /* Set CMDINDEX bits according to SDIO_CmdIndex value */
  /* Set WAITRESP bits according to SDIO_Response value */
  /* Set WAITINT and WAITPEND bits according to SDIO_Wait value */
  /* Set CPSMEN bits according to SDIO_CPSM value */
  tmpreg |= (uint32_t)SDIO_CmdInitStruct->SDIO_CmdIndex | SDIO_CmdInitStruct->SDIO_Response
           | SDIO_CmdInitStruct->SDIO_Wait | SDIO_CmdInitStruct->SDIO_CPSM;
  
  /* Write to SDIO CMD */
  SDIO->CMD = tmpreg;
}