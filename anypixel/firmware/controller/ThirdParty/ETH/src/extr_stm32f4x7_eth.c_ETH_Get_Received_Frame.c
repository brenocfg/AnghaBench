#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_10__ {TYPE_1__* FS_Rx_Desc; } ;
struct TYPE_9__ {int Status; scalar_t__ Buffer2NextDescAddr; } ;
struct TYPE_8__ {int length; int /*<<< orphan*/  buffer; TYPE_1__* descriptor; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {int /*<<< orphan*/  Buffer1Addr; } ;
typedef  TYPE_2__ FrameTypeDef ;
typedef  TYPE_3__ ETH_DMADESCTypeDef ;

/* Variables and functions */
 TYPE_3__* DMARxDescToGet ; 
 TYPE_5__* DMA_RX_FRAME_infos ; 
 int ETH_DMARxDesc_FL ; 
 int ETH_DMARxDesc_FrameLengthShift ; 

FrameTypeDef ETH_Get_Received_Frame(void)
{
  uint32_t framelength = 0;
  FrameTypeDef frame = {0,0,0};

  /* Get the Frame Length of the received packet: substruct 4 bytes of the CRC */
  framelength = ((DMARxDescToGet->Status & ETH_DMARxDesc_FL) >> ETH_DMARxDesc_FrameLengthShift) - 4;
  frame.length = framelength;

  /* Get the address of the first frame descriptor and the buffer start address */
  frame.descriptor = DMA_RX_FRAME_infos->FS_Rx_Desc;
  frame.buffer =(DMA_RX_FRAME_infos->FS_Rx_Desc)->Buffer1Addr;

  /* Update the ETHERNET DMA global Rx descriptor with next Rx descriptor */
  /* Chained Mode */
  /* Selects the next DMA Rx descriptor list for next buffer to read */
  DMARxDescToGet = (ETH_DMADESCTypeDef*) (DMARxDescToGet->Buffer2NextDescAddr);

  /* Return Frame */
  return (frame);
}