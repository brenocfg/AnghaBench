#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct request {TYPE_1__* rq_disk; int /*<<< orphan*/  end_io_data; } ;
struct TYPE_10__ {long LogicalDriveNumber; int /*<<< orphan*/  DmaDirection; int /*<<< orphan*/  SegmentCount; int /*<<< orphan*/  cmd_sglist; struct request* Request; int /*<<< orphan*/  BlockCount; int /*<<< orphan*/  BlockNumber; int /*<<< orphan*/  Completion; int /*<<< orphan*/  CommandType; } ;
struct TYPE_9__ {int /*<<< orphan*/  PCIDevice; } ;
struct TYPE_8__ {scalar_t__ private_data; } ;
typedef  TYPE_2__ DAC960_Controller_T ;
typedef  TYPE_3__ DAC960_Command_T ;

/* Variables and functions */
 TYPE_3__* DAC960_AllocateCommand (TYPE_2__*) ; 
 int /*<<< orphan*/  DAC960_QueueReadWriteCommand (TYPE_3__*) ; 
 int /*<<< orphan*/  DAC960_ReadCommand ; 
 int /*<<< orphan*/  DAC960_WriteCommand ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 scalar_t__ READ ; 
 struct request* blk_peek_request (struct request_queue*) ; 
 int /*<<< orphan*/  blk_rq_map_sg (struct request_queue*,struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_rq_pos (struct request*) ; 
 int /*<<< orphan*/  blk_rq_sectors (struct request*) ; 
 int /*<<< orphan*/  blk_start_request (struct request*) ; 
 int /*<<< orphan*/  pci_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rq_data_dir (struct request*) ; 

__attribute__((used)) static int DAC960_process_queue(DAC960_Controller_T *Controller, struct request_queue *req_q)
{
	struct request *Request;
	DAC960_Command_T *Command;

   while(1) {
	Request = blk_peek_request(req_q);
	if (!Request)
		return 1;

	Command = DAC960_AllocateCommand(Controller);
	if (Command == NULL)
		return 0;

	if (rq_data_dir(Request) == READ) {
		Command->DmaDirection = PCI_DMA_FROMDEVICE;
		Command->CommandType = DAC960_ReadCommand;
	} else {
		Command->DmaDirection = PCI_DMA_TODEVICE;
		Command->CommandType = DAC960_WriteCommand;
	}
	Command->Completion = Request->end_io_data;
	Command->LogicalDriveNumber = (long)Request->rq_disk->private_data;
	Command->BlockNumber = blk_rq_pos(Request);
	Command->BlockCount = blk_rq_sectors(Request);
	Command->Request = Request;
	blk_start_request(Request);
	Command->SegmentCount = blk_rq_map_sg(req_q,
		  Command->Request, Command->cmd_sglist);
	/* pci_map_sg MAY change the value of SegCount */
	Command->SegmentCount = pci_map_sg(Controller->PCIDevice, Command->cmd_sglist,
		 Command->SegmentCount, Command->DmaDirection);

	DAC960_QueueReadWriteCommand(Command);
  }
}