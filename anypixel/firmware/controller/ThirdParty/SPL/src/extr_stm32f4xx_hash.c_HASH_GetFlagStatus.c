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
struct TYPE_2__ {int CR; int SR; } ;
typedef  scalar_t__ FlagStatus ;

/* Variables and functions */
 TYPE_1__* HASH ; 
 int HASH_FLAG_DINNE ; 
 int /*<<< orphan*/  IS_HASH_GET_FLAG (int) ; 
 scalar_t__ RESET ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

FlagStatus HASH_GetFlagStatus(uint16_t HASH_FLAG)
{
  FlagStatus bitstatus = RESET;
  uint32_t tempreg = 0;

  /* Check the parameters */
  assert_param(IS_HASH_GET_FLAG(HASH_FLAG));

  /* check if the FLAG is in CR register */
  if ((HASH_FLAG & HASH_FLAG_DINNE) != (uint16_t)RESET ) 
  {
    tempreg = HASH->CR;
  }
  else /* The FLAG is in SR register */
  {
    tempreg = HASH->SR;
  }

  /* Check the status of the specified HASH flag */
  if ((tempreg & HASH_FLAG) != (uint16_t)RESET)
  {
    /* HASH is set */
    bitstatus = SET;
  }
  else
  {
    /* HASH_FLAG is reset */
    bitstatus = RESET;
  }

  /* Return the HASH_FLAG status */
  return  bitstatus;
}