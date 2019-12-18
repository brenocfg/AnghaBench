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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ ControlBufferSize; } ;
typedef  TYPE_1__ ETH_DMADESCTypeDef ;

/* Variables and functions */
 scalar_t__ ETH_DMARXDESC_BUFFER2_SIZESHIFT ; 
 scalar_t__ ETH_DMARxDesc_Buffer1 ; 
 scalar_t__ ETH_DMARxDesc_RBS1 ; 
 scalar_t__ ETH_DMARxDesc_RBS2 ; 
 int /*<<< orphan*/  IS_ETH_DMA_RXDESC_BUFFER (scalar_t__) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

uint32_t ETH_GetDMARxDescBufferSize(ETH_DMADESCTypeDef *DMARxDesc, uint32_t DMARxDesc_Buffer)
{
  /* Check the parameters */
  assert_param(IS_ETH_DMA_RXDESC_BUFFER(DMARxDesc_Buffer));

  if(DMARxDesc_Buffer != ETH_DMARxDesc_Buffer1)
  {
    /* Return the DMA Rx Desc buffer2 size */
    return ((DMARxDesc->ControlBufferSize & ETH_DMARxDesc_RBS2) >> ETH_DMARXDESC_BUFFER2_SIZESHIFT);
  }
  else
  {
    /* Return the DMA Rx Desc buffer1 size */
    return (DMARxDesc->ControlBufferSize & ETH_DMARxDesc_RBS1);
  }
}