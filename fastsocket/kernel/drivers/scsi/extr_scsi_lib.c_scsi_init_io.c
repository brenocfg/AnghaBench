#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nents; int /*<<< orphan*/  sgl; } ;
struct scsi_data_buffer {TYPE_1__ table; } ;
struct scsi_cmnd {TYPE_2__* request; struct scsi_data_buffer* prot_sdb; struct scsi_data_buffer sdb; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_8__ {struct scsi_data_buffer* special; struct TYPE_8__* next_rq; } ;

/* Variables and functions */
 int BLKPREP_DEFER ; 
 int BLKPREP_OK ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ blk_bidi_rq (TYPE_2__*) ; 
 scalar_t__ blk_integrity_rq (TYPE_2__*) ; 
 int blk_rq_count_integrity_sg (TYPE_2__*) ; 
 int blk_rq_map_integrity_sg (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct scsi_data_buffer* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_alloc_sgtable (struct scsi_data_buffer*,int,int /*<<< orphan*/ ) ; 
 int scsi_init_sgtable (TYPE_2__*,struct scsi_data_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_put_command (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_release_buffers (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sdb_cache ; 
 int /*<<< orphan*/  unlikely (int) ; 

int scsi_init_io(struct scsi_cmnd *cmd, gfp_t gfp_mask)
{
	int error = scsi_init_sgtable(cmd->request, &cmd->sdb, gfp_mask);
	if (error)
		goto err_exit;

	if (blk_bidi_rq(cmd->request)) {
		struct scsi_data_buffer *bidi_sdb = kmem_cache_zalloc(
			scsi_sdb_cache, GFP_ATOMIC);
		if (!bidi_sdb) {
			error = BLKPREP_DEFER;
			goto err_exit;
		}

		cmd->request->next_rq->special = bidi_sdb;
		error = scsi_init_sgtable(cmd->request->next_rq, bidi_sdb,
								    GFP_ATOMIC);
		if (error)
			goto err_exit;
	}

	if (blk_integrity_rq(cmd->request)) {
		struct scsi_data_buffer *prot_sdb = cmd->prot_sdb;
		int ivecs, count;

		BUG_ON(prot_sdb == NULL);
		ivecs = blk_rq_count_integrity_sg(cmd->request);

		if (scsi_alloc_sgtable(prot_sdb, ivecs, gfp_mask)) {
			error = BLKPREP_DEFER;
			goto err_exit;
		}

		count = blk_rq_map_integrity_sg(cmd->request,
						prot_sdb->table.sgl);
		BUG_ON(unlikely(count > ivecs));

		cmd->prot_sdb = prot_sdb;
		cmd->prot_sdb->table.nents = count;
	}

	return BLKPREP_OK ;

err_exit:
	scsi_release_buffers(cmd);
	cmd->request->special = NULL;
	scsi_put_command(cmd);
	return error;
}