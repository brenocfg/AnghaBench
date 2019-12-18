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
struct TYPE_2__ {int VTOR; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_NVIC_OFFSET (int) ; 
 int /*<<< orphan*/  IS_NVIC_VECTTAB (int) ; 
 TYPE_1__* SCB ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset)
{
  /* Check the parameters */
  assert_param(IS_NVIC_VECTTAB(NVIC_VectTab));
  assert_param(IS_NVIC_OFFSET(Offset));

  SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1FFFFF80);
}