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
struct TYPE_6__ {scalar_t__ nents; } ;
struct scsi_data_buffer {TYPE_3__ table; } ;
struct scsi_cmnd {struct scsi_data_buffer* prot_sdb; TYPE_2__* request; struct scsi_data_buffer sdb; } ;
struct TYPE_5__ {TYPE_1__* next_rq; } ;
struct TYPE_4__ {struct scsi_data_buffer* special; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct scsi_data_buffer*) ; 
 int /*<<< orphan*/  memset (struct scsi_data_buffer*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ scsi_bidi_cmnd (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_free_sgtable (struct scsi_data_buffer*) ; 
 scalar_t__ scsi_prot_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sdb_cache ; 

__attribute__((used)) static void __scsi_release_buffers(struct scsi_cmnd *cmd, int do_bidi_check)
{

	if (cmd->sdb.table.nents)
		scsi_free_sgtable(&cmd->sdb);

	memset(&cmd->sdb, 0, sizeof(cmd->sdb));

	if (do_bidi_check && scsi_bidi_cmnd(cmd)) {
		struct scsi_data_buffer *bidi_sdb =
			cmd->request->next_rq->special;
		scsi_free_sgtable(bidi_sdb);
		kmem_cache_free(scsi_sdb_cache, bidi_sdb);
		cmd->request->next_rq->special = NULL;
	}

	if (scsi_prot_sg_count(cmd))
		scsi_free_sgtable(cmd->prot_sdb);
}