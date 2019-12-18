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
typedef  int uint16_t ;
struct TYPE_2__ {int MISR; } ;
typedef  scalar_t__ ITStatus ;

/* Variables and functions */
 TYPE_1__* DCMI ; 
 int /*<<< orphan*/  IS_DCMI_GET_IT (int) ; 
 scalar_t__ RESET ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

ITStatus DCMI_GetITStatus(uint16_t DCMI_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t itstatus = 0;
  
  /* Check the parameters */
  assert_param(IS_DCMI_GET_IT(DCMI_IT));
  
  itstatus = DCMI->MISR & DCMI_IT; /* Only masked interrupts are checked */
  
  if ((itstatus != (uint16_t)RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}