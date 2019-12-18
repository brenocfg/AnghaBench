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
struct TYPE_5__ {int TR; } ;
struct TYPE_4__ {void* RTC_Seconds; void* RTC_Minutes; void* RTC_Hours; void* RTC_H12; } ;
typedef  TYPE_1__ RTC_TimeTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  IS_RTC_FORMAT (int) ; 
 TYPE_3__* RTC ; 
 scalar_t__ RTC_Bcd2ToByte (void*) ; 
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

void RTC_GetTime(uint32_t RTC_Format, RTC_TimeTypeDef* RTC_TimeStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));

  /* Get the RTC_TR register */
  tmpreg = (uint32_t)(RTC->TR & RTC_TR_RESERVED_MASK); 
  
  /* Fill the structure fields with the read parameters */
  RTC_TimeStruct->RTC_Hours = (uint8_t)((tmpreg & (RTC_TR_HT | RTC_TR_HU)) >> 16);
  RTC_TimeStruct->RTC_Minutes = (uint8_t)((tmpreg & (RTC_TR_MNT | RTC_TR_MNU)) >>8);
  RTC_TimeStruct->RTC_Seconds = (uint8_t)(tmpreg & (RTC_TR_ST | RTC_TR_SU));
  RTC_TimeStruct->RTC_H12 = (uint8_t)((tmpreg & (RTC_TR_PM)) >> 16);  

  /* Check the input parameters format */
  if (RTC_Format == RTC_Format_BIN)
  {
    /* Convert the structure parameters to Binary format */
    RTC_TimeStruct->RTC_Hours = (uint8_t)RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Hours);
    RTC_TimeStruct->RTC_Minutes = (uint8_t)RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Minutes);
    RTC_TimeStruct->RTC_Seconds = (uint8_t)RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Seconds);   
  }
}