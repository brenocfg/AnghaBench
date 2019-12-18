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
typedef  void* uint8_t ;
typedef  int uint32_t ;
struct TYPE_5__ {int DR; } ;
struct TYPE_4__ {void* RTC_Date; void* RTC_Month; void* RTC_Year; void* RTC_WeekDay; } ;
typedef  TYPE_1__ RTC_DateTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  IS_RTC_FORMAT (int) ; 
 TYPE_3__* RTC ; 
 scalar_t__ RTC_Bcd2ToByte (void*) ; 
 int RTC_DR_DT ; 
 int RTC_DR_DU ; 
 int RTC_DR_MT ; 
 int RTC_DR_MU ; 
 int RTC_DR_RESERVED_MASK ; 
 int RTC_DR_WDU ; 
 int RTC_DR_YT ; 
 int RTC_DR_YU ; 
 int RTC_Format_BIN ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void RTC_GetDate(uint32_t RTC_Format, RTC_DateTypeDef* RTC_DateStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));
  
  /* Get the RTC_TR register */
  tmpreg = (uint32_t)(RTC->DR & RTC_DR_RESERVED_MASK); 

  /* Fill the structure fields with the read parameters */
  RTC_DateStruct->RTC_Year = (uint8_t)((tmpreg & (RTC_DR_YT | RTC_DR_YU)) >> 16);
  RTC_DateStruct->RTC_Month = (uint8_t)((tmpreg & (RTC_DR_MT | RTC_DR_MU)) >> 8);
  RTC_DateStruct->RTC_Date = (uint8_t)(tmpreg & (RTC_DR_DT | RTC_DR_DU));
  RTC_DateStruct->RTC_WeekDay = (uint8_t)((tmpreg & (RTC_DR_WDU)) >> 13);

  /* Check the input parameters format */
  if (RTC_Format == RTC_Format_BIN)
  {
    /* Convert the structure parameters to Binary format */
    RTC_DateStruct->RTC_Year = (uint8_t)RTC_Bcd2ToByte(RTC_DateStruct->RTC_Year);
    RTC_DateStruct->RTC_Month = (uint8_t)RTC_Bcd2ToByte(RTC_DateStruct->RTC_Month);
    RTC_DateStruct->RTC_Date = (uint8_t)RTC_Bcd2ToByte(RTC_DateStruct->RTC_Date);
  }
}