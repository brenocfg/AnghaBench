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
typedef  int uint32_t ;
struct TYPE_2__ {int WPR; int CALIBR; } ;
typedef  scalar_t__ ErrorStatus ;

/* Variables and functions */
 scalar_t__ ERROR ; 
 int /*<<< orphan*/  IS_RTC_CALIB_SIGN (int) ; 
 int /*<<< orphan*/  IS_RTC_CALIB_VALUE (int) ; 
 TYPE_1__* RTC ; 
 scalar_t__ RTC_EnterInitMode () ; 
 int /*<<< orphan*/  RTC_ExitInitMode () ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

ErrorStatus RTC_CoarseCalibConfig(uint32_t RTC_CalibSign, uint32_t Value)
{
  ErrorStatus status = ERROR;
   
  /* Check the parameters */
  assert_param(IS_RTC_CALIB_SIGN(RTC_CalibSign));
  assert_param(IS_RTC_CALIB_VALUE(Value)); 

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
    /* Set the coarse calibration value */
    RTC->CALIBR = (uint32_t)(RTC_CalibSign | Value);
    /* Exit Initialization mode */
    RTC_ExitInitMode();
    
    status = SUCCESS;
  } 

  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF; 
  
  return status;
}