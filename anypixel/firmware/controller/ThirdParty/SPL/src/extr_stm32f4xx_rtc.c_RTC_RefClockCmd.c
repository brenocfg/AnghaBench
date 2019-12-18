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
struct TYPE_2__ {int WPR; int /*<<< orphan*/  CR; } ;
typedef  scalar_t__ FunctionalState ;
typedef  scalar_t__ ErrorStatus ;

/* Variables and functions */
 scalar_t__ DISABLE ; 
 scalar_t__ ERROR ; 
 int /*<<< orphan*/  IS_FUNCTIONAL_STATE (scalar_t__) ; 
 TYPE_1__* RTC ; 
 int /*<<< orphan*/  RTC_CR_REFCKON ; 
 scalar_t__ RTC_EnterInitMode () ; 
 int /*<<< orphan*/  RTC_ExitInitMode () ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

ErrorStatus RTC_RefClockCmd(FunctionalState NewState)
{ 
  ErrorStatus status = ERROR;
  
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
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
    if (NewState != DISABLE)
    {
      /* Enable the RTC reference clock detection */
      RTC->CR |= RTC_CR_REFCKON;   
    }
    else
    {
      /* Disable the RTC reference clock detection */
      RTC->CR &= ~RTC_CR_REFCKON;    
    }
    /* Exit Initialization mode */
    RTC_ExitInitMode();
    
    status = SUCCESS;
  }
  
  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;  
  
  return status; 
}