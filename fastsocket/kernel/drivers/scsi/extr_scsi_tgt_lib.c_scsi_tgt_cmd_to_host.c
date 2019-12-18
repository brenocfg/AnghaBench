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
struct scsi_tgt_queuedata {struct Scsi_Host* shost; } ;
struct scsi_cmnd {TYPE_2__* request; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_4__ {TYPE_1__* q; } ;
struct TYPE_3__ {struct scsi_tgt_queuedata* queuedata; } ;

/* Variables and functions */

struct Scsi_Host *scsi_tgt_cmd_to_host(struct scsi_cmnd *cmd)
{
	struct scsi_tgt_queuedata *queue = cmd->request->q->queuedata;
	return queue->shost;
}