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
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {scalar_t__ IER; } ;
typedef  scalar_t__ FunctionalState ;

/* Variables and functions */
 TYPE_1__* DCMI ; 
 scalar_t__ DISABLE ; 
 int /*<<< orphan*/  IS_DCMI_CONFIG_IT (scalar_t__) ; 
 int /*<<< orphan*/  IS_FUNCTIONAL_STATE (scalar_t__) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void DCMI_ITConfig(uint16_t DCMI_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DCMI_CONFIG_IT(DCMI_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the Interrupt sources */
    DCMI->IER |= DCMI_IT;
  }
  else
  {
    /* Disable the Interrupt sources */
    DCMI->IER &= (uint16_t)(~DCMI_IT);
  }  
}