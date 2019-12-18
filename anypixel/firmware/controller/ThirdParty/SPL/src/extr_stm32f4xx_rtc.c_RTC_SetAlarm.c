#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_7__ {scalar_t__ CR; int WPR; scalar_t__ ALRMBR; scalar_t__ ALRMAR; } ;
struct TYPE_5__ {scalar_t__ RTC_Hours; int RTC_H12; scalar_t__ RTC_Minutes; scalar_t__ RTC_Seconds; } ;
struct TYPE_6__ {scalar_t__ RTC_AlarmDateWeekDaySel; scalar_t__ RTC_AlarmDateWeekDay; scalar_t__ RTC_AlarmMask; TYPE_1__ RTC_AlarmTime; } ;
typedef  TYPE_2__ RTC_AlarmTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ALARM_MASK (scalar_t__) ; 
 int /*<<< orphan*/  IS_RTC_ALARM (scalar_t__) ; 
 int /*<<< orphan*/  IS_RTC_ALARM_DATE_WEEKDAY_DATE (scalar_t__) ; 
 int /*<<< orphan*/  IS_RTC_ALARM_DATE_WEEKDAY_SEL (scalar_t__) ; 
 int /*<<< orphan*/  IS_RTC_ALARM_DATE_WEEKDAY_WEEKDAY (scalar_t__) ; 
 int /*<<< orphan*/  IS_RTC_FORMAT (scalar_t__) ; 
 int /*<<< orphan*/  IS_RTC_H12 (int) ; 
 int /*<<< orphan*/  IS_RTC_HOUR12 (scalar_t__) ; 
 int /*<<< orphan*/  IS_RTC_HOUR24 (scalar_t__) ; 
 int /*<<< orphan*/  IS_RTC_MINUTES (scalar_t__) ; 
 int /*<<< orphan*/  IS_RTC_SECONDS (scalar_t__) ; 
 scalar_t__ RESET ; 
 TYPE_4__* RTC ; 
 scalar_t__ RTC_AlarmDateWeekDaySel_Date ; 
 scalar_t__ RTC_Alarm_A ; 
 scalar_t__ RTC_Bcd2ToByte (scalar_t__) ; 
 scalar_t__ RTC_ByteToBcd2 (scalar_t__) ; 
 scalar_t__ RTC_CR_FMT ; 
 scalar_t__ RTC_Format_BIN ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void RTC_SetAlarm(uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmTypeDef* RTC_AlarmStruct)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));
  assert_param(IS_RTC_ALARM(RTC_Alarm));
  assert_param(IS_ALARM_MASK(RTC_AlarmStruct->RTC_AlarmMask));
  assert_param(IS_RTC_ALARM_DATE_WEEKDAY_SEL(RTC_AlarmStruct->RTC_AlarmDateWeekDaySel));

  if (RTC_Format == RTC_Format_BIN)
  {
    if ((RTC->CR & RTC_CR_FMT) != (uint32_t)RESET)
    {
      assert_param(IS_RTC_HOUR12(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours));
      assert_param(IS_RTC_H12(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12));
    } 
    else
    {
      RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = 0x00;
      assert_param(IS_RTC_HOUR24(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours));
    }
    assert_param(IS_RTC_MINUTES(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes));
    assert_param(IS_RTC_SECONDS(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds));
    
    if(RTC_AlarmStruct->RTC_AlarmDateWeekDaySel == RTC_AlarmDateWeekDaySel_Date)
    {
      assert_param(IS_RTC_ALARM_DATE_WEEKDAY_DATE(RTC_AlarmStruct->RTC_AlarmDateWeekDay));
    }
    else
    {
      assert_param(IS_RTC_ALARM_DATE_WEEKDAY_WEEKDAY(RTC_AlarmStruct->RTC_AlarmDateWeekDay));
    }
  }
  else
  {
    if ((RTC->CR & RTC_CR_FMT) != (uint32_t)RESET)
    {
      tmpreg = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours);
      assert_param(IS_RTC_HOUR12(tmpreg));
      assert_param(IS_RTC_H12(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12));
    } 
    else
    {
      RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = 0x00;
      assert_param(IS_RTC_HOUR24(RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours)));
    }
    
    assert_param(IS_RTC_MINUTES(RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes)));
    assert_param(IS_RTC_SECONDS(RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds)));
    
    if(RTC_AlarmStruct->RTC_AlarmDateWeekDaySel == RTC_AlarmDateWeekDaySel_Date)
    {
      tmpreg = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDateWeekDay);
      assert_param(IS_RTC_ALARM_DATE_WEEKDAY_DATE(tmpreg));    
    }
    else
    {
      tmpreg = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDateWeekDay);
      assert_param(IS_RTC_ALARM_DATE_WEEKDAY_WEEKDAY(tmpreg));      
    }    
  }

  /* Check the input parameters format */
  if (RTC_Format != RTC_Format_BIN)
  {
    tmpreg = (((uint32_t)(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours) << 16) | \
              ((uint32_t)(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes) << 8) | \
              ((uint32_t)RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds) | \
              ((uint32_t)(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12) << 16) | \
              ((uint32_t)(RTC_AlarmStruct->RTC_AlarmDateWeekDay) << 24) | \
              ((uint32_t)RTC_AlarmStruct->RTC_AlarmDateWeekDaySel) | \
              ((uint32_t)RTC_AlarmStruct->RTC_AlarmMask)); 
  }  
  else
  {
    tmpreg = (((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours) << 16) | \
              ((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes) << 8) | \
              ((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds)) | \
              ((uint32_t)(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12) << 16) | \
              ((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmDateWeekDay) << 24) | \
              ((uint32_t)RTC_AlarmStruct->RTC_AlarmDateWeekDaySel) | \
              ((uint32_t)RTC_AlarmStruct->RTC_AlarmMask)); 
  } 

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  /* Configure the Alarm register */
  if (RTC_Alarm == RTC_Alarm_A)
  {
    RTC->ALRMAR = (uint32_t)tmpreg;
  }
  else
  {
    RTC->ALRMBR = (uint32_t)tmpreg;
  }

  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;   
}