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
typedef  int uint32_t ;
struct TYPE_2__ {int SR; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_RNG_CLEAR_FLAG (scalar_t__) ; 
 TYPE_1__* RNG ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void RNG_ClearFlag(uint8_t RNG_FLAG)
{
  /* Check the parameters */
  assert_param(IS_RNG_CLEAR_FLAG(RNG_FLAG));
  /* Clear the selected RNG flags */
  RNG->SR = ~(uint32_t)(((uint32_t)RNG_FLAG) << 4);
}