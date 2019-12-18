#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ub_scsi_cmd {scalar_t__* cdb; int cdb_len; int nsg; int /*<<< orphan*/  state; scalar_t__ tag; struct ub_scsi_cmd* back; int /*<<< orphan*/  done; int /*<<< orphan*/  lun; void* len; struct scatterlist* sgv; int /*<<< orphan*/  dir; } ;
struct ub_dev {int /*<<< orphan*/  tagcnt; scalar_t__ top_sense; struct ub_scsi_cmd top_rqs_cmd; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int EPIPE ; 
 int PAGE_SIZE ; 
 scalar_t__ REQUEST_SENSE ; 
 int /*<<< orphan*/  UB_CMDST_INIT ; 
 int /*<<< orphan*/  UB_CMDST_SENSE ; 
 int /*<<< orphan*/  UB_DIR_READ ; 
 int /*<<< orphan*/  UB_MAX_REQ_SG ; 
 void* UB_SENSE_SIZE ; 
 int /*<<< orphan*/  memset (struct ub_scsi_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,int /*<<< orphan*/ ,void*,unsigned long) ; 
 int /*<<< orphan*/  ub_cmdq_insert (struct ub_dev*,struct ub_scsi_cmd*) ; 
 int /*<<< orphan*/  ub_state_done (struct ub_dev*,struct ub_scsi_cmd*,int) ; 
 int /*<<< orphan*/  ub_top_sense_done ; 
 int /*<<< orphan*/  virt_to_page (scalar_t__) ; 

__attribute__((used)) static void ub_state_sense(struct ub_dev *sc, struct ub_scsi_cmd *cmd)
{
	struct ub_scsi_cmd *scmd;
	struct scatterlist *sg;
	int rc;

	if (cmd->cdb[0] == REQUEST_SENSE) {
		rc = -EPIPE;
		goto error;
	}

	scmd = &sc->top_rqs_cmd;
	memset(scmd, 0, sizeof(struct ub_scsi_cmd));
	scmd->cdb[0] = REQUEST_SENSE;
	scmd->cdb[4] = UB_SENSE_SIZE;
	scmd->cdb_len = 6;
	scmd->dir = UB_DIR_READ;
	scmd->state = UB_CMDST_INIT;
	scmd->nsg = 1;
	sg = &scmd->sgv[0];
	sg_init_table(sg, UB_MAX_REQ_SG);
	sg_set_page(sg, virt_to_page(sc->top_sense), UB_SENSE_SIZE,
			(unsigned long)sc->top_sense & (PAGE_SIZE-1));
	scmd->len = UB_SENSE_SIZE;
	scmd->lun = cmd->lun;
	scmd->done = ub_top_sense_done;
	scmd->back = cmd;

	scmd->tag = sc->tagcnt++;

	cmd->state = UB_CMDST_SENSE;

	ub_cmdq_insert(sc, scmd);
	return;

error:
	ub_state_done(sc, cmd, rc);
}