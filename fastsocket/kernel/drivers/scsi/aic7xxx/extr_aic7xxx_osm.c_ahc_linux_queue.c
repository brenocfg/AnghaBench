#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {void (* scsi_done ) (struct scsi_cmnd*) ;int result; TYPE_3__* device; } ;
struct ahc_softc {TYPE_1__* platform_data; } ;
struct ahc_linux_device {int dummy; } ;
struct TYPE_6__ {TYPE_2__* host; } ;
struct TYPE_5__ {scalar_t__ hostdata; } ;
struct TYPE_4__ {scalar_t__ qfrozen; } ;

/* Variables and functions */
 int CAM_REQ_INPROG ; 
 int SCSI_MLQUEUE_HOST_BUSY ; 
 int ahc_linux_run_command (struct ahc_softc*,struct ahc_linux_device*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  ahc_lock (struct ahc_softc*,unsigned long*) ; 
 int /*<<< orphan*/  ahc_unlock (struct ahc_softc*,unsigned long*) ; 
 struct ahc_linux_device* scsi_transport_device_data (TYPE_3__*) ; 

__attribute__((used)) static int
ahc_linux_queue(struct scsi_cmnd * cmd, void (*scsi_done) (struct scsi_cmnd *))
{
	struct	 ahc_softc *ahc;
	struct	 ahc_linux_device *dev = scsi_transport_device_data(cmd->device);
	int rtn = SCSI_MLQUEUE_HOST_BUSY;
	unsigned long flags;

	ahc = *(struct ahc_softc **)cmd->device->host->hostdata;

	ahc_lock(ahc, &flags);
	if (ahc->platform_data->qfrozen == 0) {
		cmd->scsi_done = scsi_done;
		cmd->result = CAM_REQ_INPROG << 16;
		rtn = ahc_linux_run_command(ahc, dev, cmd);
	}
	ahc_unlock(ahc, &flags);

	return rtn;
}