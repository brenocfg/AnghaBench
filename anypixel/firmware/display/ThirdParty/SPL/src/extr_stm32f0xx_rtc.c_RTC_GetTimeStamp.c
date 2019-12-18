#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int uint32_t ;
struct TYPE_8__ {int TSTR; int TSDR; } ;
struct TYPE_7__ {void* RTC_WeekDay; void* RTC_Date; void* RTC_Month; scalar_t__ RTC_Year; } ;
struct TYPE_6__ {void* RTC_Seconds; void* RTC_Minutes; void* RTC_Hours; void* RTC_H12; } ;
typedef  TYPE_1__ RTC_TimeTypeDef ;
typedef  TYPE_2__ RTC_DateTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  IS_RTC_FORMAT (int) ; 
 TYPE_5__* RTC ; 
 scalar_t__ RTC_Bcd2ToByte (void*) ; 
 int RTC_DR_DT ; 
 int RTC_DR_DU ; 
 int RTC_DR_MT ; 
 int RTC_DR_MU ; 
 int RTC_DR_RESERVED_MASK ; 
 int RTC_DR_WDU ; 
 int RTC_Format_BIN ; 
 int RTC_TR_HT ; 
 int RTC_TR_HU ; 
 int RTC_TR_MNT ; 
 int RTC_TR_MNU ; 
 int RTC_TR_PM ; 
 int RTC_TR_RESERVED_MASK ; 
 int RTC_TR_ST ; 
 int RTC_TR_SU ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void RTC_GetTimeStamp(uint32_t RTC_Format, RTC_TimeTypeDef* RTC_StampTimeStruct, 
                                      RTC_DateTypeDef* RTC_StampDateStruct)
{
  uint32_t tmptime = 0, tmpdate = 0;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));

  /* Get the TimeStamp time and date registers values */
  tmptime = (uint32_t)(RTC->TSTR & RTC_TR_RESERVED_MASK);
  tmpdate = (uint32_t)(RTC->TSDR & RTC_DR_RESERVED_MASK);

  /* Fill the Time structure fields with the read parameters */
  RTC_StampTimeStruct->RTC_Hours = (uint8_t)((tmptime & (RTC_TR_HT | RTC_TR_HU)) >> 16);
  RTC_StampTimeStruct->RTC_Minutes = (uint8_t)((tmptime & (RTC_TR_MNT | RTC_TR_MNU)) >> 8);
  RTC_StampTimeStruct->RTC_Seconds = (uint8_t)(tmptime & (RTC_TR_ST | RTC_TR_SU));
  RTC_StampTimeStruct->RTC_H12 = (uint8_t)((tmptime & (RTC_TR_PM)) >> 16);  

  /* Fill the Date structure fields with the read parameters */
  RTC_StampDateStruct->RTC_Year = 0;
  RTC_StampDateStruct->RTC_Month = (uint8_t)((tmpdate & (RTC_DR_MT | RTC_DR_MU)) >> 8);
  RTC_StampDateStruct->RTC_Date = (uint8_t)(tmpdate & (RTC_DR_DT | RTC_DR_DU));
  RTC_StampDateStruct->RTC_WeekDay = (uint8_t)((tmpdate & (RTC_DR_WDU)) >> 13);

  /* Check the input parameters format */
  if (RTC_Format == RTC_Format_BIN)
  {
    /* Convert the Time structure parameters to Binary format */
    RTC_StampTimeStruct->RTC_Hours = (uint8_t)RTC_Bcd2ToByte(RTC_StampTimeStruct->RTC_Hours);
    RTC_StampTimeStruct->RTC_Minutes = (uint8_t)RTC_Bcd2ToByte(RTC_StampTimeStruct->RTC_Minutes);
    RTC_StampTimeStruct->RTC_Seconds = (uint8_t)RTC_Bcd2ToByte(RTC_StampTimeStruct->RTC_Seconds);

    /* Convert the Date structure parameters to Binary format */
    RTC_StampDateStruct->RTC_Month = (uint8_t)RTC_Bcd2ToByte(RTC_StampDateStruct->RTC_Month);
    RTC_StampDateStruct->RTC_Date = (uint8_t)RTC_Bcd2ToByte(RTC_StampDateStruct->RTC_Date);
    RTC_StampDateStruct->RTC_WeekDay = (uint8_t)RTC_Bcd2ToByte(RTC_StampDateStruct->RTC_WeekDay);
  }
}