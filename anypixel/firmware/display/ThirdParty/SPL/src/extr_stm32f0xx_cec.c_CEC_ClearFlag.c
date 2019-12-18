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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  ISR; } ;

/* Variables and functions */
 TYPE_1__* CEC ; 
 int /*<<< orphan*/  IS_CEC_CLEAR_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void CEC_ClearFlag(uint32_t CEC_FLAG)
{
  assert_param(IS_CEC_CLEAR_FLAG(CEC_FLAG));

  /* Clear the selected CEC flag */
  CEC->ISR = CEC_FLAG;
}