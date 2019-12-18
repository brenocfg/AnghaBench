#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct Host {int dummy; } ;
struct TYPE_2__ {int dest_unit; int len; int* data; void* src_port; scalar_t__ src_unit; void* dest_port; } ;
struct CmdBlk {TYPE_1__ Packet; } ;

/* Variables and functions */
 void* BOOT_RUP ; 
 int EIO ; 
 int ENXIO ; 
 int IWAIT ; 
 int IWAIT_MAGIC ; 
 struct CmdBlk* RIOGetCmdBlk () ; 
 scalar_t__ RIOQueueCmdBlk (struct Host*,int,struct CmdBlk*) ; 
 int /*<<< orphan*/  RIO_DEBUG_CMD ; 
 scalar_t__ RIO_FAIL ; 
 int /*<<< orphan*/  rio_dprintk (int /*<<< orphan*/ ,char*,...) ; 

int RIOSuspendBootRta(struct Host *HostP, int ID, int Link)
{
	struct CmdBlk *CmdBlkP;

	rio_dprintk(RIO_DEBUG_CMD, "SUSPEND BOOT ON RTA ID %d, link %c\n", ID, 'A' + Link);

	CmdBlkP = RIOGetCmdBlk();

	if (!CmdBlkP) {
		rio_dprintk(RIO_DEBUG_CMD, "SUSPEND BOOT ON RTA: GetCmdBlk failed\n");
		return -ENXIO;
	}

	CmdBlkP->Packet.dest_unit = ID;
	CmdBlkP->Packet.dest_port = BOOT_RUP;
	CmdBlkP->Packet.src_unit = 0;
	CmdBlkP->Packet.src_port = BOOT_RUP;
	CmdBlkP->Packet.len = 0x84;
	CmdBlkP->Packet.data[0] = IWAIT;
	CmdBlkP->Packet.data[1] = Link;
	CmdBlkP->Packet.data[2] = IWAIT_MAGIC & 0xFF;
	CmdBlkP->Packet.data[3] = (IWAIT_MAGIC >> 8) & 0xFF;

	if (RIOQueueCmdBlk(HostP, ID - 1, CmdBlkP) == RIO_FAIL) {
		rio_dprintk(RIO_DEBUG_CMD, "SUSPEND BOOT ON RTA: Failed to queue iwait command\n");
		return -EIO;
	}
	return 0;
}