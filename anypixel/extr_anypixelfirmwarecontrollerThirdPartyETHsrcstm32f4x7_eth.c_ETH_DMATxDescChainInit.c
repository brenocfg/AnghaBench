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
struct TYPE_6__ {int DMATDLAR; } ;
struct TYPE_5__ {int Buffer1Addr; int Buffer2NextDescAddr; int /*<<< orphan*/  Status; } ;
typedef  TYPE_1__ ETH_DMADESCTypeDef ;

/* Variables and functions */
 TYPE_1__* DMATxDescToSet ; 
 TYPE_3__* ETH ; 
 int /*<<< orphan*/  ETH_DMATxDesc_TCH ; 
 int ETH_TX_BUF_SIZE ; 

void ETH_DMATxDescChainInit(ETH_DMADESCTypeDef *DMATxDescTab, uint8_t* TxBuff, uint32_t TxBuffCount)
{
  uint32_t i = 0;
  ETH_DMADESCTypeDef *DMATxDesc;

  /* Set the DMATxDescToSet pointer with the first one of the DMATxDescTab list */
  DMATxDescToSet = DMATxDescTab;
  /* Fill each DMATxDesc descriptor with the right values */
  for(i=0; i < TxBuffCount; i++)
  {
    /* Get the pointer on the ith member of the Tx Desc list */
    DMATxDesc = DMATxDescTab + i;
    /* Set Second Address Chained bit */
    DMATxDesc->Status = ETH_DMATxDesc_TCH;

    /* Set Buffer1 address pointer */
    DMATxDesc->Buffer1Addr = (uint32_t)(&TxBuff[i*ETH_TX_BUF_SIZE]);

    /* Initialize the next descriptor with the Next Descriptor Polling Enable */
    if(i < (TxBuffCount-1))
    {
      /* Set next descriptor address register with next descriptor base address */
      DMATxDesc->Buffer2NextDescAddr = (uint32_t)(DMATxDescTab+i+1);
    }
    else
    {
      /* For last descriptor, set next descriptor address register equal to the first descriptor base address */
      DMATxDesc->Buffer2NextDescAddr = (uint32_t) DMATxDescTab;
    }
  }

  /* Set Transmit Desciptor List Address Register */
  ETH->DMATDLAR = (uint32_t) DMATxDescTab;
}