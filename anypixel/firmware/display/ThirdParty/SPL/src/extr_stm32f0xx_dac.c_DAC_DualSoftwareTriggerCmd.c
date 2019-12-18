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
struct TYPE_2__ {int /*<<< orphan*/  SWTRIGR; } ;
typedef  scalar_t__ FunctionalState ;

/* Variables and functions */
 TYPE_1__* DAC ; 
 scalar_t__ DISABLE ; 
 int /*<<< orphan*/  DUAL_SWTRIG_RESET ; 
 int /*<<< orphan*/  DUAL_SWTRIG_SET ; 
 int /*<<< orphan*/  IS_FUNCTIONAL_STATE (scalar_t__) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void DAC_DualSoftwareTriggerCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable software trigger for both DAC channels */
    DAC->SWTRIGR |= DUAL_SWTRIG_SET;
  }
  else
  {
    /* Disable software trigger for both DAC channels */
    DAC->SWTRIGR &= DUAL_SWTRIG_RESET;
  }
}