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
struct TYPE_3__ {int /*<<< orphan*/  Status; } ;
typedef  TYPE_1__ ETH_DMADESCTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_DMATxDesc_OWN ; 

void ETH_SetDMATxDescOwnBit(ETH_DMADESCTypeDef *DMATxDesc)
{
  /* Set the DMA Tx Desc Own bit */
  DMATxDesc->Status |= ETH_DMATxDesc_OWN;
}