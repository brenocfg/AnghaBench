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
struct scsi_qla_host {int /*<<< orphan*/  host_no; struct req_que* req; } ;
struct scsi_device {int queue_depth; int /*<<< orphan*/  lun; int /*<<< orphan*/  id; scalar_t__ ordered_tags; TYPE_1__* hostdata; } ;
struct req_que {int max_q_depth; } ;
struct TYPE_2__ {struct scsi_qla_host* vha; } ;
typedef  TYPE_1__ fc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ORDERED_TAG ; 
 int /*<<< orphan*/  MSG_SIMPLE_TAG ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_io ; 
 int /*<<< orphan*/  scsi_adjust_queue_depth (struct scsi_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qla2x00_adjust_sdev_qdepth_up(struct scsi_device *sdev, int qdepth)
{
	fc_port_t *fcport = sdev->hostdata;
	struct scsi_qla_host *vha = fcport->vha;
	struct req_que *req = NULL;

	req = vha->req;
	if (!req)
		return;

	if (req->max_q_depth <= sdev->queue_depth || req->max_q_depth < qdepth)
		return;

	if (sdev->ordered_tags)
		scsi_adjust_queue_depth(sdev, MSG_ORDERED_TAG, qdepth);
	else
		scsi_adjust_queue_depth(sdev, MSG_SIMPLE_TAG, qdepth);

	ql_dbg(ql_dbg_io, vha, 0x302a,
	    "Queue depth adjusted-up to %d for nexus=%ld:%d:%d.\n",
	    sdev->queue_depth, fcport->vha->host_no, sdev->id, sdev->lun);
}