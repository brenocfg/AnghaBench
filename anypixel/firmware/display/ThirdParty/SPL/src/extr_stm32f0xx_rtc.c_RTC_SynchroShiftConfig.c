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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int WPR; int ISR; int CR; scalar_t__ SHIFTR; } ;
typedef  scalar_t__ ErrorStatus ;

/* Variables and functions */
 scalar_t__ ERROR ; 
 int /*<<< orphan*/  IS_RTC_SHIFT_ADD1S (scalar_t__) ; 
 int /*<<< orphan*/  IS_RTC_SHIFT_SUBFS (scalar_t__) ; 
 int RESET ; 
 TYPE_1__* RTC ; 
 int RTC_CR_REFCKON ; 
 int RTC_ISR_SHPF ; 
 scalar_t__ RTC_WaitForSynchro () ; 
 scalar_t__ SHPF_TIMEOUT ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

ErrorStatus RTC_SynchroShiftConfig(uint32_t RTC_ShiftAdd1S, uint32_t RTC_ShiftSubFS)
{
  ErrorStatus status = ERROR;
  uint32_t shpfcount = 0;

  /* Check the parameters */
  assert_param(IS_RTC_SHIFT_ADD1S(RTC_ShiftAdd1S));
  assert_param(IS_RTC_SHIFT_SUBFS(RTC_ShiftSubFS));

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;
  
  /* Check if a Shift is pending*/
  if ((RTC->ISR & RTC_ISR_SHPF) != RESET)
  {
    /* Wait until the shift is completed*/
    while (((RTC->ISR & RTC_ISR_SHPF) != RESET) && (shpfcount != SHPF_TIMEOUT))
    {
      shpfcount++;
    }
  }

  /* Check if the Shift pending is completed or if there is no Shift operation at all*/
  if ((RTC->ISR & RTC_ISR_SHPF) == RESET)
  {
    /* check if the reference clock detection is disabled */
    if((RTC->CR & RTC_CR_REFCKON) == RESET)
    {
      /* Configure the Shift settings */
      RTC->SHIFTR = (uint32_t)(uint32_t)(RTC_ShiftSubFS) | (uint32_t)(RTC_ShiftAdd1S);
    
      if(RTC_WaitForSynchro() == ERROR)
      {
        status = ERROR;
      }
      else
      {
        status = SUCCESS;
      }
    }
    else
    {
      status = ERROR;
    }
  }
  else
  {
    status = ERROR;
  }

  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;
  
  return (ErrorStatus)(status);
}