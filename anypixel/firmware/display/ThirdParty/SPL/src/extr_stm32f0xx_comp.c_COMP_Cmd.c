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
struct TYPE_2__ {int CSR; } ;
typedef  scalar_t__ FunctionalState ;

/* Variables and functions */
 TYPE_1__* COMP ; 
 scalar_t__ DISABLE ; 
 int /*<<< orphan*/  IS_COMP_ALL_PERIPH (int) ; 
 int /*<<< orphan*/  IS_FUNCTIONAL_STATE (scalar_t__) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void COMP_Cmd(uint32_t COMP_Selection, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected COMP peripheral */
    COMP->CSR |= (uint32_t) (1<<COMP_Selection);
  }
  else
  {
    /* Disable the selected COMP peripheral  */
    COMP->CSR &= (uint32_t)(~((uint32_t)1<<COMP_Selection));
  }
}