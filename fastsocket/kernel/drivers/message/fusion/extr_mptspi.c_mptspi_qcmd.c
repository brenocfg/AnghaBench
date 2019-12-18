#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int result; TYPE_2__* device; } ;
struct _MPT_SCSI_HOST {int /*<<< orphan*/ * ioc; } ;
struct TYPE_3__ {int /*<<< orphan*/  vtarget; } ;
typedef  TYPE_1__ VirtDevice ;
struct TYPE_4__ {int channel; int /*<<< orphan*/  id; TYPE_1__* hostdata; int /*<<< orphan*/  host; } ;
typedef  int /*<<< orphan*/  MPT_ADAPTER ;

/* Variables and functions */
 int DID_NO_CONNECT ; 
 int /*<<< orphan*/  ddvprintk (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mptscsih_is_phys_disk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mptscsih_qcmd (struct scsi_cmnd*,void (*) (struct scsi_cmnd*)) ; 
 int /*<<< orphan*/  scsi_print_command (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_target (TYPE_2__*) ; 
 struct _MPT_SCSI_HOST* shost_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ spi_dv_pending (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mptspi_qcmd(struct scsi_cmnd *SCpnt, void (*done)(struct scsi_cmnd *))
{
	struct _MPT_SCSI_HOST *hd = shost_priv(SCpnt->device->host);
	VirtDevice	*vdevice = SCpnt->device->hostdata;
	MPT_ADAPTER *ioc = hd->ioc;

	if (!vdevice || !vdevice->vtarget) {
		SCpnt->result = DID_NO_CONNECT << 16;
		done(SCpnt);
		return 0;
	}

	if (SCpnt->device->channel == 1 &&
		mptscsih_is_phys_disk(ioc, 0, SCpnt->device->id) == 0) {
		SCpnt->result = DID_NO_CONNECT << 16;
		done(SCpnt);
		return 0;
	}

	if (spi_dv_pending(scsi_target(SCpnt->device)))
		ddvprintk(ioc, scsi_print_command(SCpnt));

	return mptscsih_qcmd(SCpnt,done);
}