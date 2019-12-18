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
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {scalar_t__ SR; } ;

/* Variables and functions */
 TYPE_1__* HASH ; 
 int /*<<< orphan*/  IS_HASH_IT (scalar_t__) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void HASH_ClearITPendingBit(uint8_t HASH_IT)
{
  /* Check the parameters */
  assert_param(IS_HASH_IT(HASH_IT));

  /* Clear the selected HASH interrupt pending bit */
  HASH->SR = (uint8_t)~HASH_IT;
}