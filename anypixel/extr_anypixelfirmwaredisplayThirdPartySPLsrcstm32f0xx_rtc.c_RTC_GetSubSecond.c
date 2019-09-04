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
struct TYPE_2__ {int /*<<< orphan*/  DR; scalar_t__ SSR; } ;

/* Variables and functions */
 TYPE_1__* RTC ; 

uint32_t RTC_GetSubSecond(void)
{
  uint32_t tmpreg = 0;
  
  /* Get subseconds values from the correspondent registers*/
  tmpreg = (uint32_t)(RTC->SSR);
  
  /* Read DR register to unfroze calendar registers */
  (void) (RTC->DR);
  
  return (tmpreg);
}