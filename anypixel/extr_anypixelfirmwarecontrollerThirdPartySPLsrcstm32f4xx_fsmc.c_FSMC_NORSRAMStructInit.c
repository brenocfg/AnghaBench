#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* FSMC_WriteTimingStruct; TYPE_1__* FSMC_ReadWriteTimingStruct; int /*<<< orphan*/  FSMC_WriteBurst; int /*<<< orphan*/  FSMC_ExtendedMode; int /*<<< orphan*/  FSMC_WaitSignal; int /*<<< orphan*/  FSMC_WriteOperation; int /*<<< orphan*/  FSMC_WaitSignalActive; int /*<<< orphan*/  FSMC_WrapMode; int /*<<< orphan*/  FSMC_WaitSignalPolarity; int /*<<< orphan*/  FSMC_AsynchronousWait; int /*<<< orphan*/  FSMC_BurstAccessMode; int /*<<< orphan*/  FSMC_MemoryDataWidth; int /*<<< orphan*/  FSMC_MemoryType; int /*<<< orphan*/  FSMC_DataAddressMux; int /*<<< orphan*/  FSMC_Bank; } ;
struct TYPE_6__ {int FSMC_AddressSetupTime; int FSMC_AddressHoldTime; int FSMC_DataSetupTime; int FSMC_BusTurnAroundDuration; int FSMC_CLKDivision; int FSMC_DataLatency; void* FSMC_AccessMode; } ;
struct TYPE_5__ {int FSMC_AddressSetupTime; int FSMC_AddressHoldTime; int FSMC_DataSetupTime; int FSMC_BusTurnAroundDuration; int FSMC_CLKDivision; int FSMC_DataLatency; void* FSMC_AccessMode; } ;
typedef  TYPE_3__ FSMC_NORSRAMInitTypeDef ;

/* Variables and functions */
 void* FSMC_AccessMode_A ; 
 int /*<<< orphan*/  FSMC_AsynchronousWait_Disable ; 
 int /*<<< orphan*/  FSMC_Bank1_NORSRAM1 ; 
 int /*<<< orphan*/  FSMC_BurstAccessMode_Disable ; 
 int /*<<< orphan*/  FSMC_DataAddressMux_Enable ; 
 int /*<<< orphan*/  FSMC_ExtendedMode_Disable ; 
 int /*<<< orphan*/  FSMC_MemoryDataWidth_8b ; 
 int /*<<< orphan*/  FSMC_MemoryType_SRAM ; 
 int /*<<< orphan*/  FSMC_WaitSignalActive_BeforeWaitState ; 
 int /*<<< orphan*/  FSMC_WaitSignalPolarity_Low ; 
 int /*<<< orphan*/  FSMC_WaitSignal_Enable ; 
 int /*<<< orphan*/  FSMC_WrapMode_Disable ; 
 int /*<<< orphan*/  FSMC_WriteBurst_Disable ; 
 int /*<<< orphan*/  FSMC_WriteOperation_Enable ; 

void FSMC_NORSRAMStructInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct)
{  
  /* Reset NOR/SRAM Init structure parameters values */
  FSMC_NORSRAMInitStruct->FSMC_Bank = FSMC_Bank1_NORSRAM1;
  FSMC_NORSRAMInitStruct->FSMC_DataAddressMux = FSMC_DataAddressMux_Enable;
  FSMC_NORSRAMInitStruct->FSMC_MemoryType = FSMC_MemoryType_SRAM;
  FSMC_NORSRAMInitStruct->FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_8b;
  FSMC_NORSRAMInitStruct->FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  FSMC_NORSRAMInitStruct->FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
  FSMC_NORSRAMInitStruct->FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  FSMC_NORSRAMInitStruct->FSMC_WrapMode = FSMC_WrapMode_Disable;
  FSMC_NORSRAMInitStruct->FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_NORSRAMInitStruct->FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  FSMC_NORSRAMInitStruct->FSMC_WaitSignal = FSMC_WaitSignal_Enable;
  FSMC_NORSRAMInitStruct->FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  FSMC_NORSRAMInitStruct->FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AddressSetupTime = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AddressHoldTime = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_DataSetupTime = 0xFF;
  FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_BusTurnAroundDuration = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_CLKDivision = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_DataLatency = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AccessMode = FSMC_AccessMode_A; 
  FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AddressSetupTime = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AddressHoldTime = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_DataSetupTime = 0xFF;
  FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_BusTurnAroundDuration = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_CLKDivision = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_DataLatency = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AccessMode = FSMC_AccessMode_A;
}