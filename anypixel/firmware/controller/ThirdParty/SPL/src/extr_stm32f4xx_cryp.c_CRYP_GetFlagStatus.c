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
struct TYPE_2__ {int RISR; int SR; } ;
typedef  scalar_t__ FlagStatus ;

/* Variables and functions */
 TYPE_1__* CRYP ; 
 int FLAG_MASK ; 
 int /*<<< orphan*/  IS_CRYP_GET_FLAG (int) ; 
 scalar_t__ RESET ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

FlagStatus CRYP_GetFlagStatus(uint8_t CRYP_FLAG)
{
  FlagStatus bitstatus = RESET;
  uint32_t tempreg = 0;

  /* Check the parameters */
  assert_param(IS_CRYP_GET_FLAG(CRYP_FLAG));

  /* check if the FLAG is in RISR register */
  if ((CRYP_FLAG & FLAG_MASK) != 0x00) 
  {
    tempreg = CRYP->RISR;
  }
  else  /* The FLAG is in SR register */
  {
    tempreg = CRYP->SR;
  }


  /* Check the status of the specified CRYP flag */
  if ((tempreg & CRYP_FLAG ) != (uint8_t)RESET)
  {
    /* CRYP_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* CRYP_FLAG is reset */
    bitstatus = RESET;
  }

  /* Return the CRYP_FLAG status */
  return  bitstatus;
}