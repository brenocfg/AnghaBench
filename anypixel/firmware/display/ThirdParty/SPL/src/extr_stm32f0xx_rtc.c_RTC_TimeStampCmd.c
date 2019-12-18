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
struct TYPE_2__ {int CR; int WPR; } ;
typedef  scalar_t__ FunctionalState ;

/* Variables and functions */
 scalar_t__ DISABLE ; 
 int /*<<< orphan*/  IS_FUNCTIONAL_STATE (scalar_t__) ; 
 int /*<<< orphan*/  IS_RTC_TIMESTAMP_EDGE (int) ; 
 TYPE_1__* RTC ; 
 int RTC_CR_TSE ; 
 int RTC_CR_TSEDGE ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void RTC_TimeStampCmd(uint32_t RTC_TimeStampEdge, FunctionalState NewState)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RTC_TIMESTAMP_EDGE(RTC_TimeStampEdge));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Get the RTC_CR register and clear the bits to be configured */
  tmpreg = (uint32_t)(RTC->CR & (uint32_t)~(RTC_CR_TSEDGE | RTC_CR_TSE));

  /* Get the new configuration */
  if (NewState != DISABLE)
  {
    tmpreg |= (uint32_t)(RTC_TimeStampEdge | RTC_CR_TSE);
  }
  else
  {
    tmpreg |= (uint32_t)(RTC_TimeStampEdge);
  }

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  /* Configure the Time Stamp TSEDGE and Enable bits */
  RTC->CR = (uint32_t)tmpreg;

  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;
}