#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int Seg_Count; TYPE_1__* LS_Rx_Desc; TYPE_1__* FS_Rx_Desc; } ;
struct TYPE_4__ {int Status; scalar_t__ Buffer2NextDescAddr; } ;
typedef  TYPE_1__ ETH_DMADESCTypeDef ;

/* Variables and functions */
 TYPE_1__* DMARxDescToGet ; 
 TYPE_2__* DMA_RX_FRAME_infos ; 
 int ETH_DMARxDesc_FS ; 
 int ETH_DMARxDesc_LS ; 
 int ETH_DMARxDesc_OWN ; 
 scalar_t__ RESET ; 

uint32_t ETH_CheckFrameReceived(void)
{
  /* check if last segment */
  if(((DMARxDescToGet->Status & ETH_DMARxDesc_OWN) == (uint32_t)RESET) &&
     ((DMARxDescToGet->Status & ETH_DMARxDesc_LS) != (uint32_t)RESET))
  {
    DMA_RX_FRAME_infos->Seg_Count++;
    if (DMA_RX_FRAME_infos->Seg_Count == 1)
    {
      DMA_RX_FRAME_infos->FS_Rx_Desc = DMARxDescToGet;
    }
    DMA_RX_FRAME_infos->LS_Rx_Desc = DMARxDescToGet;
    return 1;
  }

  /* check if first segment */
  else if(((DMARxDescToGet->Status & ETH_DMARxDesc_OWN) == (uint32_t)RESET) &&
          ((DMARxDescToGet->Status & ETH_DMARxDesc_FS) != (uint32_t)RESET)&&
            ((DMARxDescToGet->Status & ETH_DMARxDesc_LS) == (uint32_t)RESET))
  {
    DMA_RX_FRAME_infos->FS_Rx_Desc = DMARxDescToGet;
    DMA_RX_FRAME_infos->LS_Rx_Desc = NULL;
    DMA_RX_FRAME_infos->Seg_Count = 1;
    DMARxDescToGet = (ETH_DMADESCTypeDef*) (DMARxDescToGet->Buffer2NextDescAddr);
  }

  /* check if intermediate segment */
  else if(((DMARxDescToGet->Status & ETH_DMARxDesc_OWN) == (uint32_t)RESET) &&
          ((DMARxDescToGet->Status & ETH_DMARxDesc_FS) == (uint32_t)RESET)&&
            ((DMARxDescToGet->Status & ETH_DMARxDesc_LS) == (uint32_t)RESET))
  {
    (DMA_RX_FRAME_infos->Seg_Count) ++;
    DMARxDescToGet = (ETH_DMADESCTypeDef*) (DMARxDescToGet->Buffer2NextDescAddr);
  }
  return 0;
}