#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int ControlBufferSize; } ;
typedef  TYPE_1__ ETH_DMADESCTypeDef ;

/* Variables and functions */
 int ETH_DMATXDESC_BUFFER2_SIZESHIFT ; 
 int /*<<< orphan*/  IS_ETH_DMATxDESC_BUFFER_SIZE (int) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void ETH_DMATxDescBufferSizeConfig(ETH_DMADESCTypeDef *DMATxDesc, uint32_t BufferSize1, uint32_t BufferSize2)
{
  /* Check the parameters */
  assert_param(IS_ETH_DMATxDESC_BUFFER_SIZE(BufferSize1));
  assert_param(IS_ETH_DMATxDESC_BUFFER_SIZE(BufferSize2));

  /* Set the DMA Tx Desc buffer1 and buffer2 sizes values */
  DMATxDesc->ControlBufferSize |= (BufferSize1 | (BufferSize2 << ETH_DMATXDESC_BUFFER2_SIZESHIFT));
}