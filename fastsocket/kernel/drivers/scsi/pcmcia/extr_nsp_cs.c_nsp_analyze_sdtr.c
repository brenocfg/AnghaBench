#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int SyncPeriod; unsigned int SyncOffset; unsigned int SyncRegister; unsigned int AckWidth; } ;
typedef  TYPE_3__ sync_data ;
struct scsi_cmnd {TYPE_2__* device; } ;
struct nsp_sync_table {unsigned int max_period; unsigned int min_period; unsigned int chip_period; unsigned int ack_width; } ;
struct TYPE_8__ {int ScsiClockDiv; TYPE_3__* Sync; } ;
typedef  TYPE_4__ nsp_hw_data ;
struct TYPE_6__ {TYPE_1__* host; } ;
struct TYPE_5__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int BIT (int) ; 
 int CLOCK_20M ; 
 int FALSE ; 
 int /*<<< orphan*/  NSP_DEBUG_SYNC ; 
 unsigned int SYNCREG_OFFSET_MASK ; 
 unsigned int SYNCREG_PERIOD_SHIFT ; 
 int TRUE ; 
 int /*<<< orphan*/  nsp_dbg (int /*<<< orphan*/ ,char*,...) ; 
 struct nsp_sync_table* nsp_sync_table_20M ; 
 struct nsp_sync_table* nsp_sync_table_40M ; 
 unsigned char scmd_id (struct scsi_cmnd*) ; 

__attribute__((used)) static int nsp_analyze_sdtr(struct scsi_cmnd *SCpnt)
{
	unsigned char	       target = scmd_id(SCpnt);
//	unsigned char	       lun    = SCpnt->device->lun;
	nsp_hw_data           *data   = (nsp_hw_data *)SCpnt->device->host->hostdata;
	sync_data	      *sync   = &(data->Sync[target]);
	struct nsp_sync_table *sync_table;
	unsigned int	       period, offset;
	int		       i;


	nsp_dbg(NSP_DEBUG_SYNC, "in");

	period = sync->SyncPeriod;
	offset = sync->SyncOffset;

	nsp_dbg(NSP_DEBUG_SYNC, "period=0x%x, offset=0x%x", period, offset);

	if ((data->ScsiClockDiv & (BIT(0)|BIT(1))) == CLOCK_20M) {
		sync_table = nsp_sync_table_20M;
	} else {
		sync_table = nsp_sync_table_40M;
	}

	for ( i = 0; sync_table->max_period != 0; i++, sync_table++) {
		if ( period >= sync_table->min_period &&
		     period <= sync_table->max_period	 ) {
			break;
		}
	}

	if (period != 0 && sync_table->max_period == 0) {
		/*
		 * No proper period/offset found
		 */
		nsp_dbg(NSP_DEBUG_SYNC, "no proper period/offset");

		sync->SyncPeriod      = 0;
		sync->SyncOffset      = 0;
		sync->SyncRegister    = 0;
		sync->AckWidth	      = 0;

		return FALSE;
	}

	sync->SyncRegister    = (sync_table->chip_period << SYNCREG_PERIOD_SHIFT) |
		                (offset & SYNCREG_OFFSET_MASK);
	sync->AckWidth	      = sync_table->ack_width;

	nsp_dbg(NSP_DEBUG_SYNC, "sync_reg=0x%x, ack_width=0x%x", sync->SyncRegister, sync->AckWidth);

	return TRUE;
}