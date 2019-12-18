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
struct TYPE_2__ {int MISR; } ;
typedef  scalar_t__ ITStatus ;

/* Variables and functions */
 TYPE_1__* CRYP ; 
 int /*<<< orphan*/  IS_CRYP_GET_IT (int) ; 
 scalar_t__ RESET ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

ITStatus CRYP_GetITStatus(uint8_t CRYP_IT)
{
  ITStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_CRYP_GET_IT(CRYP_IT));

  /* Check the status of the specified CRYP interrupt */
  if ((CRYP->MISR &  CRYP_IT) != (uint8_t)RESET)
  {
    /* CRYP_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* CRYP_IT is reset */
    bitstatus = RESET;
  }
  /* Return the CRYP_IT status */
  return bitstatus;
}