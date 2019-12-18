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
struct scsi_cmnd {TYPE_1__* request; } ;
struct ata_queued_cmd {scalar_t__ extrabytes; scalar_t__ nbytes; struct scsi_cmnd* scsicmd; } ;
struct TYPE_2__ {scalar_t__ extra_len; } ;

/* Variables and functions */
 scalar_t__ scsi_bufflen (struct scsi_cmnd*) ; 

__attribute__((used)) static void ata_qc_set_pc_nbytes(struct ata_queued_cmd *qc)
{
	struct scsi_cmnd *scmd = qc->scsicmd;

	qc->extrabytes = scmd->request->extra_len;
	qc->nbytes = scsi_bufflen(scmd) + qc->extrabytes;
}