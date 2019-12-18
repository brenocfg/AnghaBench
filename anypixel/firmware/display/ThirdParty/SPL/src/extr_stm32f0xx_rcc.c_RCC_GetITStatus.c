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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int CIR; } ;
typedef  scalar_t__ ITStatus ;

/* Variables and functions */
 int /*<<< orphan*/  IS_RCC_GET_IT (int) ; 
 TYPE_1__* RCC ; 
 scalar_t__ RESET ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

ITStatus RCC_GetITStatus(uint8_t RCC_IT)
{
  ITStatus bitstatus = RESET;
  
  /* Check the parameters */
  assert_param(IS_RCC_GET_IT(RCC_IT));
  
  /* Check the status of the specified RCC interrupt */
  if ((RCC->CIR & RCC_IT) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the RCC_IT status */
  return  bitstatus;
}