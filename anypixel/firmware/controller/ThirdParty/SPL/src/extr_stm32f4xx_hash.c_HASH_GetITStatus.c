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
struct TYPE_2__ {int SR; int IMR; } ;
typedef  int ITStatus ;

/* Variables and functions */
 TYPE_1__* HASH ; 
 int /*<<< orphan*/  IS_HASH_GET_IT (int) ; 
 int RESET ; 
 int SET ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

ITStatus HASH_GetITStatus(uint8_t HASH_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_HASH_GET_IT(HASH_IT));  


  /* Check the status of the specified HASH interrupt */
  tmpreg =  HASH->SR;

  if (((HASH->IMR & tmpreg) & HASH_IT) != RESET)
  {
    /* HASH_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* HASH_IT is reset */
    bitstatus = RESET;
  }
  /* Return the HASH_IT status */
  return bitstatus;
}