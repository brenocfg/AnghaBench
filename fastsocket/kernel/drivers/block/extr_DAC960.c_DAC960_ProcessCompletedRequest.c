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
struct request {int dummy; } ;
struct TYPE_5__ {int BlockCount; int /*<<< orphan*/ * Completion; int /*<<< orphan*/  DmaDirection; int /*<<< orphan*/  SegmentCount; int /*<<< orphan*/  cmd_sglist; TYPE_1__* Controller; struct request* Request; } ;
struct TYPE_4__ {int /*<<< orphan*/  PCIDevice; } ;
typedef  TYPE_2__ DAC960_Command_T ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  __blk_end_request (struct request*,int,int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool DAC960_ProcessCompletedRequest(DAC960_Command_T *Command,
						 bool SuccessfulIO)
{
	struct request *Request = Command->Request;
	int Error = SuccessfulIO ? 0 : -EIO;

	pci_unmap_sg(Command->Controller->PCIDevice, Command->cmd_sglist,
		Command->SegmentCount, Command->DmaDirection);

	 if (!__blk_end_request(Request, Error, Command->BlockCount << 9)) {
		if (Command->Completion) {
			complete(Command->Completion);
			Command->Completion = NULL;
		}
		return true;
	}
	return false;
}