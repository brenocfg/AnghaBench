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
struct TYPE_2__ {int /*<<< orphan*/  ICR; } ;

/* Variables and functions */
 TYPE_1__* DCMI ; 
 int /*<<< orphan*/  IS_DCMI_CLEAR_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void DCMI_ClearFlag(uint16_t DCMI_FLAG)
{
  /* Check the parameters */
  assert_param(IS_DCMI_CLEAR_FLAG(DCMI_FLAG));
  
  /* Clear the flag by writing in the ICR register 1 in the corresponding 
  Flag position*/
  
  DCMI->ICR = DCMI_FLAG;
}