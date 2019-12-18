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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ CR; } ;
typedef  scalar_t__ FunctionalState ;

/* Variables and functions */
 scalar_t__ DISABLE ; 
 int /*<<< orphan*/  IS_FUNCTIONAL_STATE (scalar_t__) ; 
 TYPE_1__* PWR ; 
 scalar_t__ PWR_CR_DBP ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void PWR_BackupAccessCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the Backup Domain Access */
    PWR->CR |= PWR_CR_DBP;
  }
  else
  {
    /* Disable the Backup Domain Access */
    PWR->CR &= (uint32_t)~((uint32_t)PWR_CR_DBP);
  } 
}