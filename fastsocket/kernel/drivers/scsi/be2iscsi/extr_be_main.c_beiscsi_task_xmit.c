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
struct scsi_cmnd {scalar_t__ sc_data_direction; } ;
struct scatterlist {int dummy; } ;
struct iscsi_task {struct iscsi_conn* conn; struct scsi_cmnd* sc; struct beiscsi_io_task* dd_data; } ;
struct iscsi_conn {scalar_t__ dd_data; } ;
struct beiscsi_io_task {struct scsi_cmnd* scsi_cmnd; } ;
struct beiscsi_hba {int (* iotask_fn ) (struct iscsi_task*,struct scatterlist*,int,unsigned int,unsigned int) ;} ;
struct beiscsi_conn {struct beiscsi_hba* phba; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_IO ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int beiscsi_mtask (struct iscsi_task*) ; 
 unsigned int scsi_bufflen (struct scsi_cmnd*) ; 
 int scsi_dma_map (struct scsi_cmnd*) ; 
 struct scatterlist* scsi_sglist (struct scsi_cmnd*) ; 
 int stub1 (struct iscsi_task*,struct scatterlist*,int,unsigned int,unsigned int) ; 

__attribute__((used)) static int beiscsi_task_xmit(struct iscsi_task *task)
{
	struct beiscsi_io_task *io_task = task->dd_data;
	struct scsi_cmnd *sc = task->sc;
	struct beiscsi_hba *phba = NULL;
	struct scatterlist *sg;
	int num_sg;
	unsigned int  writedir = 0, xferlen = 0;

	phba = ((struct beiscsi_conn *)task->conn->dd_data)->phba;

	if (!sc)
		return beiscsi_mtask(task);

	io_task->scsi_cmnd = sc;
	num_sg = scsi_dma_map(sc);
	if (num_sg < 0) {
		struct iscsi_conn *conn = task->conn;
		struct beiscsi_hba *phba = NULL;

		phba = ((struct beiscsi_conn *)conn->dd_data)->phba;
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_IO,
			    "BM_%d : scsi_dma_map Failed\n");

		return num_sg;
	}
	xferlen = scsi_bufflen(sc);
	sg = scsi_sglist(sc);
	if (sc->sc_data_direction == DMA_TO_DEVICE)
		writedir = 1;
	 else
		writedir = 0;

	 return phba->iotask_fn(task, sg, num_sg, xferlen, writedir);
}