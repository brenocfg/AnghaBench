#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_6__ {int DMARDLAR; } ;
struct TYPE_5__ {int ControlBufferSize; int Buffer1Addr; int Buffer2NextDescAddr; int /*<<< orphan*/  Status; } ;
typedef  TYPE_1__ ETH_DMADESCTypeDef ;

/* Variables and functions */
 TYPE_1__* DMARxDescToGet ; 
 int /*<<< orphan*/ * DMA_RX_FRAME_infos ; 
 TYPE_3__* ETH ; 
 int /*<<< orphan*/  ETH_DMARxDesc_OWN ; 
 int ETH_DMARxDesc_RCH ; 
 int ETH_RX_BUF_SIZE ; 
 int /*<<< orphan*/  RX_Frame_Descriptor ; 

void ETH_DMARxDescChainInit(ETH_DMADESCTypeDef *DMARxDescTab, uint8_t *RxBuff, uint32_t RxBuffCount)
{
  uint32_t i = 0;
  ETH_DMADESCTypeDef *DMARxDesc;

  /* Set the DMARxDescToGet pointer with the first one of the DMARxDescTab list */
  DMARxDescToGet = DMARxDescTab;
  /* Fill each DMARxDesc descriptor with the right values */
  for(i=0; i < RxBuffCount; i++)
  {
    /* Get the pointer on the ith member of the Rx Desc list */
    DMARxDesc = DMARxDescTab+i;
    /* Set Own bit of the Rx descriptor Status */
    DMARxDesc->Status = ETH_DMARxDesc_OWN;

    /* Set Buffer1 size and Second Address Chained bit */
    DMARxDesc->ControlBufferSize = ETH_DMARxDesc_RCH | (uint32_t)ETH_RX_BUF_SIZE;
    /* Set Buffer1 address pointer */
    DMARxDesc->Buffer1Addr = (uint32_t)(&RxBuff[i*ETH_RX_BUF_SIZE]);

    /* Initialize the next descriptor with the Next Descriptor Polling Enable */
    if(i < (RxBuffCount-1))
    {
      /* Set next descriptor address register with next descriptor base address */
      DMARxDesc->Buffer2NextDescAddr = (uint32_t)(DMARxDescTab+i+1);
    }
    else
    {
      /* For last descriptor, set next descriptor address register equal to the first descriptor base address */
      DMARxDesc->Buffer2NextDescAddr = (uint32_t)(DMARxDescTab);
    }
  }

  /* Set Receive Descriptor List Address Register */
  ETH->DMARDLAR = (uint32_t) DMARxDescTab;

  DMA_RX_FRAME_infos = &RX_Frame_Descriptor;

}