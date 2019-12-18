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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int WPR; int /*<<< orphan*/  PRER; int /*<<< orphan*/  CR; } ;
struct TYPE_4__ {int RTC_AsynchPrediv; scalar_t__ RTC_SynchPrediv; scalar_t__ RTC_HourFormat; } ;
typedef  TYPE_1__ RTC_InitTypeDef ;
typedef  scalar_t__ ErrorStatus ;

/* Variables and functions */
 scalar_t__ ERROR ; 
 int /*<<< orphan*/  IS_RTC_ASYNCH_PREDIV (int) ; 
 int /*<<< orphan*/  IS_RTC_HOUR_FORMAT (scalar_t__) ; 
 int /*<<< orphan*/  IS_RTC_SYNCH_PREDIV (scalar_t__) ; 
 TYPE_3__* RTC ; 
 scalar_t__ RTC_CR_FMT ; 
 scalar_t__ RTC_EnterInitMode () ; 
 int /*<<< orphan*/  RTC_ExitInitMode () ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

ErrorStatus RTC_Init(RTC_InitTypeDef* RTC_InitStruct)
{
  ErrorStatus status = ERROR;

  /* Check the parameters */
  assert_param(IS_RTC_HOUR_FORMAT(RTC_InitStruct->RTC_HourFormat));
  assert_param(IS_RTC_ASYNCH_PREDIV(RTC_InitStruct->RTC_AsynchPrediv));
  assert_param(IS_RTC_SYNCH_PREDIV(RTC_InitStruct->RTC_SynchPrediv));

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  /* Set Initialization mode */
  if (RTC_EnterInitMode() == ERROR)
  {
    status = ERROR;
  }
  else
  {
    /* Clear RTC CR FMT Bit */
    RTC->CR &= ((uint32_t)~(RTC_CR_FMT));
    /* Set RTC_CR register */
    RTC->CR |=  ((uint32_t)(RTC_InitStruct->RTC_HourFormat));
  
    /* Configure the RTC PRER */
    RTC->PRER = (uint32_t)(RTC_InitStruct->RTC_SynchPrediv);
    RTC->PRER |= (uint32_t)(RTC_InitStruct->RTC_AsynchPrediv << 16);

    /* Exit Initialization mode */
    RTC_ExitInitMode();

    status = SUCCESS;
  }
  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;

  return status;
}