#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  neg_t ;
struct TYPE_7__ {int /*<<< orphan*/  async_stp; int /*<<< orphan*/  SCp; int /*<<< orphan*/  phase; int /*<<< orphan*/  msgs; } ;
struct TYPE_6__ {int capabilities; int asyncperiod; int /*<<< orphan*/  disconnect_ok; } ;
struct TYPE_9__ {int rst_bus_status; int /*<<< orphan*/  eh_wait; TYPE_3__* device; TYPE_2__ scsi; TYPE_1__ ifcfg; int /*<<< orphan*/ * SCpnt; } ;
struct TYPE_8__ {int period; scalar_t__ wide_xfer; scalar_t__ sof; int /*<<< orphan*/  stp; int /*<<< orphan*/  sync_state; int /*<<< orphan*/  disconnect_ok; } ;
typedef  TYPE_4__ FAS216_Info ;

/* Variables and functions */
 int FASCAP_DMA ; 
 int FASCAP_PSEUDODMA ; 
 int /*<<< orphan*/  PHASE_IDLE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msgqueue_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  neg_invalid ; 
 int /*<<< orphan*/  neg_wait ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fas216_bus_reset(FAS216_Info *info)
{
	neg_t sync_state;
	int i;

	msgqueue_flush(&info->scsi.msgs);

	sync_state = neg_invalid;

#ifdef SCSI2_SYNC
	if (info->ifcfg.capabilities & (FASCAP_DMA|FASCAP_PSEUDODMA))
		sync_state = neg_wait;
#endif

	info->scsi.phase = PHASE_IDLE;
	info->SCpnt = NULL; /* bug! */
	memset(&info->scsi.SCp, 0, sizeof(info->scsi.SCp));

	for (i = 0; i < 8; i++) {
		info->device[i].disconnect_ok	= info->ifcfg.disconnect_ok;
		info->device[i].sync_state	= sync_state;
		info->device[i].period		= info->ifcfg.asyncperiod / 4;
		info->device[i].stp		= info->scsi.async_stp;
		info->device[i].sof		= 0;
		info->device[i].wide_xfer	= 0;
	}

	info->rst_bus_status = 1;
	wake_up(&info->eh_wait);
}