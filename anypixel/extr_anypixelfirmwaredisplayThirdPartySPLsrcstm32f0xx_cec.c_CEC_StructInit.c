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
struct TYPE_3__ {int /*<<< orphan*/  CEC_SFTOption; int /*<<< orphan*/  CEC_BRDNoGen; int /*<<< orphan*/  CEC_LongBitPeriodError; int /*<<< orphan*/  CEC_BitRisingError; int /*<<< orphan*/  CEC_StopReception; int /*<<< orphan*/  CEC_RxTolerance; int /*<<< orphan*/  CEC_SignalFreeTime; } ;
typedef  TYPE_1__ CEC_InitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  CEC_BRDNoGen_Off ; 
 int /*<<< orphan*/  CEC_BitRisingError_Off ; 
 int /*<<< orphan*/  CEC_LongBitPeriodError_Off ; 
 int /*<<< orphan*/  CEC_RxTolerance_Standard ; 
 int /*<<< orphan*/  CEC_SFTOption_Off ; 
 int /*<<< orphan*/  CEC_SignalFreeTime_Standard ; 
 int /*<<< orphan*/  CEC_StopReception_Off ; 

void CEC_StructInit(CEC_InitTypeDef* CEC_InitStruct)
{
  CEC_InitStruct->CEC_SignalFreeTime = CEC_SignalFreeTime_Standard;
  CEC_InitStruct->CEC_RxTolerance = CEC_RxTolerance_Standard;
  CEC_InitStruct->CEC_StopReception = CEC_StopReception_Off;
  CEC_InitStruct->CEC_BitRisingError = CEC_BitRisingError_Off;
  CEC_InitStruct->CEC_LongBitPeriodError = CEC_LongBitPeriodError_Off;
  CEC_InitStruct->CEC_BRDNoGen = CEC_BRDNoGen_Off;
  CEC_InitStruct->CEC_SFTOption = CEC_SFTOption_Off;
}