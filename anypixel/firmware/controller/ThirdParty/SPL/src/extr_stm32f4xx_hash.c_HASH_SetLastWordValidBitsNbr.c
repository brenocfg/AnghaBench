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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  STR; } ;

/* Variables and functions */
 TYPE_1__* HASH ; 
 int /*<<< orphan*/  HASH_STR_NBW ; 
 int /*<<< orphan*/  IS_HASH_VALIDBITSNUMBER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void HASH_SetLastWordValidBitsNbr(uint16_t ValidNumber)
{
  /* Check the parameters */
  assert_param(IS_HASH_VALIDBITSNUMBER(ValidNumber));
  
  /* Configure the Number of valid bits in last word of the message */
  HASH->STR &= ~(HASH_STR_NBW);
  HASH->STR |= ValidNumber;
}