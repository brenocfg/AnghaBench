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
struct TYPE_2__ {int SR; } ;

/* Variables and functions */
 TYPE_1__* DAC ; 
 int /*<<< orphan*/  IS_DAC_CHANNEL (int) ; 
 int /*<<< orphan*/  IS_DAC_FLAG (int) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void DAC_ClearFlag(uint32_t DAC_Channel, uint32_t DAC_FLAG)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_FLAG(DAC_FLAG));

  /* Clear the selected DAC flags */
  DAC->SR = (DAC_FLAG << DAC_Channel);
}