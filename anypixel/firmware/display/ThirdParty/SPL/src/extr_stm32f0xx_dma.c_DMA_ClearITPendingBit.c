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
struct TYPE_2__ {int /*<<< orphan*/  IFCR; } ;

/* Variables and functions */
 TYPE_1__* DMA1 ; 
 int /*<<< orphan*/  IS_DMA_CLEAR_IT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void DMA_ClearITPendingBit(uint32_t DMA_IT)
{
  /* Check the parameters */
  assert_param(IS_DMA_CLEAR_IT(DMA_IT));

  /* Clear the selected DMA interrupt pending bits */
  DMA1->IFCR = DMA_IT;
}