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
struct TYPE_2__ {int SR; } ;
typedef  scalar_t__ ITStatus ;

/* Variables and functions */
 int /*<<< orphan*/  IS_RNG_GET_IT (int) ; 
 scalar_t__ RESET ; 
 TYPE_1__* RNG ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

ITStatus RNG_GetITStatus(uint8_t RNG_IT)
{
  ITStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_RNG_GET_IT(RNG_IT));

  /* Check the status of the specified RNG interrupt */
  if ((RNG->SR & RNG_IT) != (uint8_t)RESET)
  {
    /* RNG_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* RNG_IT is reset */
    bitstatus = RESET;
  }
  /* Return the RNG_IT status */
  return bitstatus;
}