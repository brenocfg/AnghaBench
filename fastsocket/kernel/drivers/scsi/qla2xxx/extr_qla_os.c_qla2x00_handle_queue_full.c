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
struct scsi_device {int /*<<< orphan*/  lun; int /*<<< orphan*/  id; int /*<<< orphan*/  queue_depth; scalar_t__ hostdata; } ;
struct fc_port {TYPE_1__* vha; } ;
typedef  struct fc_port fc_port_t ;
struct TYPE_2__ {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_1__*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_io ; 
 int /*<<< orphan*/  scsi_track_queue_full (struct scsi_device*,int) ; 

__attribute__((used)) static void qla2x00_handle_queue_full(struct scsi_device *sdev, int qdepth)
{
	fc_port_t *fcport = (struct fc_port *) sdev->hostdata;

	if (!scsi_track_queue_full(sdev, qdepth))
		return;

	ql_dbg(ql_dbg_io, fcport->vha, 0x3029,
	    "Queue depth adjusted-down to %d for nexus=%ld:%d:%d.\n",
	    sdev->queue_depth, fcport->vha->host_no, sdev->id, sdev->lun);
}