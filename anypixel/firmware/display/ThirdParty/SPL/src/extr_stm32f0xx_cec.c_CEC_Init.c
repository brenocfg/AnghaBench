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
struct TYPE_5__ {int CFGR; } ;
struct TYPE_4__ {int CEC_SignalFreeTime; int CEC_RxTolerance; int CEC_StopReception; int CEC_BitRisingError; int CEC_LongBitPeriodError; int CEC_BRDNoGen; int CEC_SFTOption; } ;
typedef  TYPE_1__ CEC_InitTypeDef ;

/* Variables and functions */
 TYPE_3__* CEC ; 
 int CFGR_CLEAR_MASK ; 
 int /*<<< orphan*/  IS_CEC_BDR_NO_GEN_ERROR (int) ; 
 int /*<<< orphan*/  IS_CEC_BIT_RISING_ERROR (int) ; 
 int /*<<< orphan*/  IS_CEC_LONG_BIT_PERIOD_ERROR (int) ; 
 int /*<<< orphan*/  IS_CEC_RX_TOLERANCE (int) ; 
 int /*<<< orphan*/  IS_CEC_SFT_OPTION (int) ; 
 int /*<<< orphan*/  IS_CEC_SIGNAL_FREE_TIME (int) ; 
 int /*<<< orphan*/  IS_CEC_STOP_RECEPTION (int) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void CEC_Init(CEC_InitTypeDef* CEC_InitStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_CEC_SIGNAL_FREE_TIME(CEC_InitStruct->CEC_SignalFreeTime));
  assert_param(IS_CEC_RX_TOLERANCE(CEC_InitStruct->CEC_RxTolerance));
  assert_param(IS_CEC_STOP_RECEPTION(CEC_InitStruct->CEC_StopReception));
  assert_param(IS_CEC_BIT_RISING_ERROR(CEC_InitStruct->CEC_BitRisingError));
  assert_param(IS_CEC_LONG_BIT_PERIOD_ERROR(CEC_InitStruct->CEC_LongBitPeriodError));
  assert_param(IS_CEC_BDR_NO_GEN_ERROR(CEC_InitStruct->CEC_BRDNoGen));
  assert_param(IS_CEC_SFT_OPTION(CEC_InitStruct->CEC_SFTOption));

  /* Get the CEC CFGR value */
  tmpreg = CEC->CFGR;

  /* Clear CFGR bits */
  tmpreg &= CFGR_CLEAR_MASK;

  /* Configure the CEC peripheral */
  tmpreg |= (CEC_InitStruct->CEC_SignalFreeTime | CEC_InitStruct->CEC_RxTolerance |
             CEC_InitStruct->CEC_StopReception  | CEC_InitStruct->CEC_BitRisingError |
             CEC_InitStruct->CEC_LongBitPeriodError| CEC_InitStruct->CEC_BRDNoGen |
             CEC_InitStruct->CEC_SFTOption);

  /* Write to CEC CFGR  register */
  CEC->CFGR = tmpreg;
}