#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct TYPE_5__ {int /*<<< orphan*/  done; int /*<<< orphan*/  status; int /*<<< orphan*/  reply; } ;
struct MPT2SAS_ADAPTER {int port_enable_failed; int start_scan_failed; TYPE_1__ port_enable_cmds; scalar_t__ start_scan; scalar_t__ is_driver_loading; } ;
struct TYPE_6__ {scalar_t__ Function; int MsgLength; int /*<<< orphan*/  IOCStatus; } ;
typedef  TYPE_2__ MPI2DefaultReply_t ;

/* Variables and functions */
 scalar_t__ MPI2_FUNCTION_EVENT_ACK ; 
 int MPI2_IOCSTATUS_MASK ; 
 int MPI2_IOCSTATUS_SUCCESS ; 
 int /*<<< orphan*/  MPT2_CMD_COMPLETE ; 
 int /*<<< orphan*/  MPT2_CMD_NOT_USED ; 
 int /*<<< orphan*/  MPT2_CMD_PENDING ; 
 int /*<<< orphan*/  MPT2_CMD_REPLY_VALID ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 TYPE_2__* mpt2sas_base_get_reply_virt_addr (struct MPT2SAS_ADAPTER*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt2sas_port_enable_complete (struct MPT2SAS_ADAPTER*) ; 

u8
mpt2sas_port_enable_done(struct MPT2SAS_ADAPTER *ioc, u16 smid, u8 msix_index,
	u32 reply)
{
	MPI2DefaultReply_t *mpi_reply;
	u16 ioc_status;

	mpi_reply = mpt2sas_base_get_reply_virt_addr(ioc, reply);
	if (mpi_reply && mpi_reply->Function == MPI2_FUNCTION_EVENT_ACK)
		return 1;

	if (ioc->port_enable_cmds.status == MPT2_CMD_NOT_USED)
		return 1;

	ioc->port_enable_cmds.status |= MPT2_CMD_COMPLETE;
	if (mpi_reply) {
		ioc->port_enable_cmds.status |= MPT2_CMD_REPLY_VALID;
		memcpy(ioc->port_enable_cmds.reply, mpi_reply,
		    mpi_reply->MsgLength*4);
	}
	ioc->port_enable_cmds.status &= ~MPT2_CMD_PENDING;

	ioc_status = le16_to_cpu(mpi_reply->IOCStatus) & MPI2_IOCSTATUS_MASK;

	if (ioc_status != MPI2_IOCSTATUS_SUCCESS)
		ioc->port_enable_failed = 1;

	if (ioc->is_driver_loading) {
		if (ioc_status == MPI2_IOCSTATUS_SUCCESS) {
			mpt2sas_port_enable_complete(ioc);
			return 1;
		} else {
			ioc->start_scan_failed = ioc_status;
			ioc->start_scan = 0;
			return 1;
		}
	}
	complete(&ioc->port_enable_cmds.done);
	return 1;
}