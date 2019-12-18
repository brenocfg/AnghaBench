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
struct scsi_tgt_cmd {int /*<<< orphan*/  bio; } ;
struct TYPE_2__ {int /*<<< orphan*/  length; } ;
struct scsi_cmnd {TYPE_1__ sdb; struct request* request; } ;
struct request_queue {int dummy; } ;
struct request {int /*<<< orphan*/  bio; struct request_queue* q; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  blk_rq_bytes (struct request*) ; 
 int blk_rq_map_user (struct request_queue*,struct request*,int /*<<< orphan*/ *,void*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  eprintk (char*,unsigned int) ; 
 int scsi_init_io (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_release_buffers (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_unmap_user_pages (struct scsi_tgt_cmd*) ; 

__attribute__((used)) static int scsi_map_user_pages(struct scsi_tgt_cmd *tcmd, struct scsi_cmnd *cmd,
			       unsigned long uaddr, unsigned int len, int rw)
{
	struct request_queue *q = cmd->request->q;
	struct request *rq = cmd->request;
	int err;

	dprintk("%lx %u\n", uaddr, len);
	err = blk_rq_map_user(q, rq, NULL, (void *)uaddr, len, GFP_KERNEL);
	if (err) {
		/*
		 * TODO: need to fixup sg_tablesize, max_segment_size,
		 * max_sectors, etc for modern HW and software drivers
		 * where this value is bogus.
		 *
		 * TODO2: we can alloc a reserve buffer of max size
		 * we can handle and do the slow copy path for really large
		 * IO.
		 */
		eprintk("Could not handle request of size %u.\n", len);
		return err;
	}

	tcmd->bio = rq->bio;
	err = scsi_init_io(cmd, GFP_KERNEL);
	if (err) {
		scsi_release_buffers(cmd);
		goto unmap_rq;
	}
	/*
	 * we use REQ_TYPE_BLOCK_PC so scsi_init_io doesn't set the
	 * length for us.
	 */
	cmd->sdb.length = blk_rq_bytes(rq);

	return 0;

unmap_rq:
	scsi_unmap_user_pages(tcmd);
	return err;
}