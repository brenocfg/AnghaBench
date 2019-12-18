#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct scatterlist {int dummy; } ;
struct TYPE_15__ {int /*<<< orphan*/ * LogicalDriveToVirtualDevice; } ;
struct TYPE_23__ {TYPE_1__ V2; } ;
struct TYPE_17__ {int ScatterGatherList0Length; int /*<<< orphan*/  ScatterGatherList0Address; } ;
struct TYPE_19__ {TYPE_7__* ScatterGatherSegments; TYPE_3__ ExtendedScatterGather; } ;
struct TYPE_16__ {int DataTransferControllerToHost; int AdditionalScatterGatherListMemory; } ;
struct TYPE_20__ {int DataTransferSize; int RequestSenseSize; int CDBLength; int* SCSI_CDB; TYPE_5__ DataTransferMemoryAddress; TYPE_2__ CommandControlBits; int /*<<< orphan*/  PhysicalDevice; int /*<<< orphan*/  RequestSenseBusAddress; int /*<<< orphan*/  CommandOpcode; } ;
struct TYPE_22__ {TYPE_6__ SCSI_10; } ;
struct TYPE_21__ {int SegmentByteCount; void* SegmentDataPointer; } ;
struct TYPE_18__ {int /*<<< orphan*/  ScatterGatherListDMA; TYPE_7__* ScatterGatherList; int /*<<< orphan*/  RequestSenseDMA; struct scatterlist* ScatterList; TYPE_8__ CommandMailbox; } ;
struct TYPE_14__ {scalar_t__ DmaDirection; int BlockCount; size_t LogicalDriveNumber; int BlockNumber; int SegmentCount; TYPE_4__ V2; TYPE_9__* Controller; } ;
typedef  TYPE_7__ DAC960_V2_ScatterGatherSegment_T ;
typedef  TYPE_8__ DAC960_V2_CommandMailbox_T ;
typedef  int /*<<< orphan*/  DAC960_SCSI_RequestSense_T ;
typedef  TYPE_9__ DAC960_Controller_T ;
typedef  TYPE_10__ DAC960_Command_T ;
typedef  int DAC960_ByteCount64_T ;
typedef  void* DAC960_BusAddress64_T ;

/* Variables and functions */
 int DAC960_BlockSizeBits ; 
 int /*<<< orphan*/  DAC960_QueueCommand (TYPE_10__*) ; 
 int /*<<< orphan*/  DAC960_V2_ClearCommand (TYPE_10__*) ; 
 int /*<<< orphan*/  DAC960_V2_SCSI_10 ; 
 scalar_t__ PCI_DMA_FROMDEVICE ; 
 scalar_t__ sg_dma_address (struct scatterlist*) ; 
 scalar_t__ sg_dma_len (struct scatterlist*) ; 

__attribute__((used)) static void DAC960_V2_QueueReadWriteCommand(DAC960_Command_T *Command)
{
  DAC960_Controller_T *Controller = Command->Controller;
  DAC960_V2_CommandMailbox_T *CommandMailbox = &Command->V2.CommandMailbox;
  struct scatterlist *ScatterList = Command->V2.ScatterList;

  DAC960_V2_ClearCommand(Command);

  CommandMailbox->SCSI_10.CommandOpcode = DAC960_V2_SCSI_10;
  CommandMailbox->SCSI_10.CommandControlBits.DataTransferControllerToHost =
    (Command->DmaDirection == PCI_DMA_FROMDEVICE);
  CommandMailbox->SCSI_10.DataTransferSize =
    Command->BlockCount << DAC960_BlockSizeBits;
  CommandMailbox->SCSI_10.RequestSenseBusAddress = Command->V2.RequestSenseDMA;
  CommandMailbox->SCSI_10.PhysicalDevice =
    Controller->V2.LogicalDriveToVirtualDevice[Command->LogicalDriveNumber];
  CommandMailbox->SCSI_10.RequestSenseSize = sizeof(DAC960_SCSI_RequestSense_T);
  CommandMailbox->SCSI_10.CDBLength = 10;
  CommandMailbox->SCSI_10.SCSI_CDB[0] =
    (Command->DmaDirection == PCI_DMA_FROMDEVICE ? 0x28 : 0x2A);
  CommandMailbox->SCSI_10.SCSI_CDB[2] = Command->BlockNumber >> 24;
  CommandMailbox->SCSI_10.SCSI_CDB[3] = Command->BlockNumber >> 16;
  CommandMailbox->SCSI_10.SCSI_CDB[4] = Command->BlockNumber >> 8;
  CommandMailbox->SCSI_10.SCSI_CDB[5] = Command->BlockNumber;
  CommandMailbox->SCSI_10.SCSI_CDB[7] = Command->BlockCount >> 8;
  CommandMailbox->SCSI_10.SCSI_CDB[8] = Command->BlockCount;

  if (Command->SegmentCount == 1)
    {
      CommandMailbox->SCSI_10.DataTransferMemoryAddress
			     .ScatterGatherSegments[0]
			     .SegmentDataPointer =
	(DAC960_BusAddress64_T)sg_dma_address(ScatterList);
      CommandMailbox->SCSI_10.DataTransferMemoryAddress
			     .ScatterGatherSegments[0]
			     .SegmentByteCount =
	CommandMailbox->SCSI_10.DataTransferSize;
    }
  else
    {
      DAC960_V2_ScatterGatherSegment_T *ScatterGatherList;
      int i;

      if (Command->SegmentCount > 2)
	{
          ScatterGatherList = Command->V2.ScatterGatherList;
	  CommandMailbox->SCSI_10.CommandControlBits
			 .AdditionalScatterGatherListMemory = true;
	  CommandMailbox->SCSI_10.DataTransferMemoryAddress
		.ExtendedScatterGather.ScatterGatherList0Length = Command->SegmentCount;
	  CommandMailbox->SCSI_10.DataTransferMemoryAddress
			 .ExtendedScatterGather.ScatterGatherList0Address =
	    Command->V2.ScatterGatherListDMA;
	}
      else
	ScatterGatherList = CommandMailbox->SCSI_10.DataTransferMemoryAddress
				 .ScatterGatherSegments;

      for (i = 0; i < Command->SegmentCount; i++, ScatterList++, ScatterGatherList++) {
		ScatterGatherList->SegmentDataPointer =
			(DAC960_BusAddress64_T)sg_dma_address(ScatterList);
		ScatterGatherList->SegmentByteCount =
			(DAC960_ByteCount64_T)sg_dma_len(ScatterList);
      }
    }
  DAC960_QueueCommand(Command);
}