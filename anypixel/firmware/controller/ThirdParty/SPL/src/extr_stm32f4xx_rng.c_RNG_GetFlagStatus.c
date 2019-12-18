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
typedef  scalar_t__ FlagStatus ;

/* Variables and functions */
 int /*<<< orphan*/  IS_RNG_GET_FLAG (int) ; 
 scalar_t__ RESET ; 
 TYPE_1__* RNG ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

FlagStatus RNG_GetFlagStatus(uint8_t RNG_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_RNG_GET_FLAG(RNG_FLAG));

  /* Check the status of the specified RNG flag */
  if ((RNG->SR & RNG_FLAG) != (uint8_t)RESET)
  {
    /* RNG_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* RNG_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the RNG_FLAG status */
  return  bitstatus;
}