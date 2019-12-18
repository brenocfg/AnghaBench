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
struct TYPE_2__ {int /*<<< orphan*/  IER; } ;
typedef  scalar_t__ FunctionalState ;

/* Variables and functions */
 TYPE_1__* CEC ; 
 scalar_t__ DISABLE ; 
 int /*<<< orphan*/  IS_CEC_IT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_FUNCTIONAL_STATE (scalar_t__) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void CEC_ITConfig(uint16_t CEC_IT, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_CEC_IT(CEC_IT));

  if (NewState != DISABLE)
  {
    /* Enable the selected CEC interrupt */
    CEC->IER |= CEC_IT;
  }
  else
  {
    CEC_IT =~CEC_IT;
    /* Disable the selected CEC interrupt */
    CEC->IER &= CEC_IT;
  }
}