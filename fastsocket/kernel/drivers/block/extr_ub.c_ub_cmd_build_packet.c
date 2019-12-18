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
struct ub_scsi_cmd {int nsg; int cdb_len; int /*<<< orphan*/  timeo; scalar_t__ len; int /*<<< orphan*/  cdb; int /*<<< orphan*/ * sgv; int /*<<< orphan*/  dir; } ;
struct ub_request {int nsg; int /*<<< orphan*/  sgv; struct request* rq; } ;
struct ub_lun {int dummy; } ;
struct ub_dev {int dummy; } ;
struct scatterlist {int dummy; } ;
struct request {int cmd_len; int /*<<< orphan*/  timeout; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  UB_DIR_NONE ; 
 int /*<<< orphan*/  UB_DIR_READ ; 
 int /*<<< orphan*/  UB_DIR_WRITE ; 
 scalar_t__ WRITE ; 
 scalar_t__ blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rq_data_dir (struct request*) ; 

__attribute__((used)) static void ub_cmd_build_packet(struct ub_dev *sc, struct ub_lun *lun,
    struct ub_scsi_cmd *cmd, struct ub_request *urq)
{
	struct request *rq = urq->rq;

	if (blk_rq_bytes(rq) == 0) {
		cmd->dir = UB_DIR_NONE;
	} else {
		if (rq_data_dir(rq) == WRITE)
			cmd->dir = UB_DIR_WRITE;
		else
			cmd->dir = UB_DIR_READ;
	}

	cmd->nsg = urq->nsg;
	memcpy(cmd->sgv, urq->sgv, sizeof(struct scatterlist) * cmd->nsg);

	memcpy(&cmd->cdb, rq->cmd, rq->cmd_len);
	cmd->cdb_len = rq->cmd_len;

	cmd->len = blk_rq_bytes(rq);

	/*
	 * To reapply this to every URB is not as incorrect as it looks.
	 * In return, we avoid any complicated tracking calculations.
	 */
	cmd->timeo = rq->timeout;
}