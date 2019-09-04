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
struct TYPE_3__ {int SDIO_DataTimeOut; int SDIO_DataLength; int /*<<< orphan*/  SDIO_DPSM; int /*<<< orphan*/  SDIO_TransferMode; int /*<<< orphan*/  SDIO_TransferDir; int /*<<< orphan*/  SDIO_DataBlockSize; } ;
typedef  TYPE_1__ SDIO_DataInitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  SDIO_DPSM_Disable ; 
 int /*<<< orphan*/  SDIO_DataBlockSize_1b ; 
 int /*<<< orphan*/  SDIO_TransferDir_ToCard ; 
 int /*<<< orphan*/  SDIO_TransferMode_Block ; 

void SDIO_DataStructInit(SDIO_DataInitTypeDef* SDIO_DataInitStruct)
{
  /* SDIO_DataInitStruct members default value */
  SDIO_DataInitStruct->SDIO_DataTimeOut = 0xFFFFFFFF;
  SDIO_DataInitStruct->SDIO_DataLength = 0x00;
  SDIO_DataInitStruct->SDIO_DataBlockSize = SDIO_DataBlockSize_1b;
  SDIO_DataInitStruct->SDIO_TransferDir = SDIO_TransferDir_ToCard;
  SDIO_DataInitStruct->SDIO_TransferMode = SDIO_TransferMode_Block;  
  SDIO_DataInitStruct->SDIO_DPSM = SDIO_DPSM_Disable;
}