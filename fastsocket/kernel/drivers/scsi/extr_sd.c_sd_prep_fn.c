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
struct scsi_disk {int /*<<< orphan*/  protection_type; } ;
struct scsi_device {int sector_size; int /*<<< orphan*/  host; int /*<<< orphan*/  writeable; scalar_t__ last_sector_bug; scalar_t__ changed; } ;
struct TYPE_3__ {unsigned int length; } ;
struct scsi_cmnd {int* cmnd; unsigned int transfersize; unsigned int underflow; int /*<<< orphan*/  allowed; TYPE_1__ sdb; TYPE_2__* device; int /*<<< orphan*/  cmd_len; int /*<<< orphan*/  sc_data_direction; } ;
struct request_queue {struct scsi_device* queuedata; } ;
struct request {int cmd_flags; scalar_t__ cmd_type; struct scsi_cmnd* special; struct gendisk* rq_disk; } ;
struct gendisk {int dummy; } ;
typedef  scalar_t__ sector_t ;
typedef  int /*<<< orphan*/  block ;
struct TYPE_4__ {scalar_t__ use_10_for_rw; } ;

/* Variables and functions */
 int BLKPREP_DEFER ; 
 int BLKPREP_KILL ; 
 int BLKPREP_OK ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 scalar_t__ READ ; 
 int READ_10 ; 
 int READ_16 ; 
 int READ_32 ; 
 int READ_6 ; 
 int REQ_DISCARD ; 
 int REQ_FLUSH ; 
 int REQ_FUA ; 
 scalar_t__ REQ_TYPE_BLOCK_PC ; 
 scalar_t__ REQ_TYPE_FS ; 
 int /*<<< orphan*/  SCSI_LOG_HLQUEUE (int,int /*<<< orphan*/ ) ; 
 int SD_DIF_TYPE2_PROTECTION ; 
 int /*<<< orphan*/  SD_EXT_CDB_SIZE ; 
 int SD_LAST_BUGGY_SECTORS ; 
 int /*<<< orphan*/  SD_MAX_RETRIES ; 
 int VARIABLE_LENGTH_CMD ; 
 scalar_t__ WRITE ; 
 int WRITE_32 ; 
 int WRITE_6 ; 
 scalar_t__ blk_integrity_rq (struct request*) ; 
 scalar_t__ blk_rq_pos (struct request*) ; 
 int blk_rq_sectors (struct request*) ; 
 scalar_t__ get_capacity (struct gendisk*) ; 
 int* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*,...) ; 
 int /*<<< orphan*/  scsi_device_online (struct scsi_device*) ; 
 scalar_t__ scsi_device_protection (TYPE_2__*) ; 
 struct scsi_disk* scsi_disk (struct gendisk*) ; 
 int scsi_host_dif_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int scsi_prep_return (struct request_queue*,struct request*,int) ; 
 scalar_t__ scsi_prot_sg_count (struct scsi_cmnd*) ; 
 int scsi_setup_blk_pc_cmnd (struct scsi_device*,struct request*) ; 
 int scsi_setup_flush_cmnd (struct scsi_device*,struct request*) ; 
 int scsi_setup_fs_cmnd (struct scsi_device*,struct request*) ; 
 int /*<<< orphan*/  sd_cdb_pool ; 
 int /*<<< orphan*/  sd_dif_prepare (struct request*,scalar_t__,int) ; 
 int /*<<< orphan*/  sd_prot_op (struct scsi_cmnd*,int) ; 
 int sd_setup_discard_cmnd (struct scsi_device*,struct request*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int sd_prep_fn(struct request_queue *q, struct request *rq)
{
	struct scsi_cmnd *SCpnt;
	struct scsi_device *sdp = q->queuedata;
	struct gendisk *disk = rq->rq_disk;
	struct scsi_disk *sdkp;
	sector_t block = blk_rq_pos(rq);
	sector_t threshold;
	unsigned int this_count = blk_rq_sectors(rq);
	int ret, host_dif;
	unsigned char protect;

	/*
	 * Discard request come in as REQ_TYPE_FS but we turn them into
	 * block PC requests to make life easier.
	 */
	if (rq->cmd_flags & REQ_DISCARD) {
		ret = sd_setup_discard_cmnd(sdp, rq);
		goto out;
	} else if (rq->cmd_flags & REQ_FLUSH) {
		ret = scsi_setup_flush_cmnd(sdp, rq);
		goto out;
	} else if (rq->cmd_type == REQ_TYPE_BLOCK_PC) {
		ret = scsi_setup_blk_pc_cmnd(sdp, rq);
		goto out;
	} else if (rq->cmd_type != REQ_TYPE_FS) {
		ret = BLKPREP_KILL;
		goto out;
	}
	ret = scsi_setup_fs_cmnd(sdp, rq);
	if (ret != BLKPREP_OK)
		goto out;
	SCpnt = rq->special;
	sdkp = scsi_disk(disk);

	/* from here on until we're complete, any goto out
	 * is used for a killable error condition */
	ret = BLKPREP_KILL;

	SCSI_LOG_HLQUEUE(1, scmd_printk(KERN_INFO, SCpnt,
					"sd_init_command: block=%llu, "
					"count=%d\n",
					(unsigned long long)block,
					this_count));

	if (!sdp || !scsi_device_online(sdp) ||
	    block + blk_rq_sectors(rq) > get_capacity(disk)) {
		SCSI_LOG_HLQUEUE(2, scmd_printk(KERN_INFO, SCpnt,
						"Finishing %u sectors\n",
						blk_rq_sectors(rq)));
		SCSI_LOG_HLQUEUE(2, scmd_printk(KERN_INFO, SCpnt,
						"Retry with 0x%p\n", SCpnt));
		goto out;
	}

	if (sdp->changed) {
		/*
		 * quietly refuse to do anything to a changed disc until 
		 * the changed bit has been reset
		 */
		/* printk("SCSI disk has been changed. Prohibiting further I/O.\n"); */
		goto out;
	}

	/*
	 * Some SD card readers can't handle multi-sector accesses which touch
	 * the last one or two hardware sectors.  Split accesses as needed.
	 */
	threshold = get_capacity(disk) - SD_LAST_BUGGY_SECTORS *
		(sdp->sector_size / 512);

	if (unlikely(sdp->last_sector_bug && block + this_count > threshold)) {
		if (block < threshold) {
			/* Access up to the threshold but not beyond */
			this_count = threshold - block;
		} else {
			/* Access only a single hardware sector */
			this_count = sdp->sector_size / 512;
		}
	}

	SCSI_LOG_HLQUEUE(2, scmd_printk(KERN_INFO, SCpnt, "block=%llu\n",
					(unsigned long long)block));

	/*
	 * If we have a 1K hardware sectorsize, prevent access to single
	 * 512 byte sectors.  In theory we could handle this - in fact
	 * the scsi cdrom driver must be able to handle this because
	 * we typically use 1K blocksizes, and cdroms typically have
	 * 2K hardware sectorsizes.  Of course, things are simpler
	 * with the cdrom, since it is read-only.  For performance
	 * reasons, the filesystems should be able to handle this
	 * and not force the scsi disk driver to use bounce buffers
	 * for this.
	 */
	if (sdp->sector_size == 1024) {
		if ((block & 1) || (blk_rq_sectors(rq) & 1)) {
			scmd_printk(KERN_ERR, SCpnt,
				    "Bad block number requested\n");
			goto out;
		} else {
			block = block >> 1;
			this_count = this_count >> 1;
		}
	}
	if (sdp->sector_size == 2048) {
		if ((block & 3) || (blk_rq_sectors(rq) & 3)) {
			scmd_printk(KERN_ERR, SCpnt,
				    "Bad block number requested\n");
			goto out;
		} else {
			block = block >> 2;
			this_count = this_count >> 2;
		}
	}
	if (sdp->sector_size == 4096) {
		if ((block & 7) || (blk_rq_sectors(rq) & 7)) {
			scmd_printk(KERN_ERR, SCpnt,
				    "Bad block number requested\n");
			goto out;
		} else {
			block = block >> 3;
			this_count = this_count >> 3;
		}
	}
	if (rq_data_dir(rq) == WRITE) {
		if (!sdp->writeable) {
			goto out;
		}
		SCpnt->cmnd[0] = WRITE_6;
		SCpnt->sc_data_direction = DMA_TO_DEVICE;

		if (blk_integrity_rq(rq))
			sd_dif_prepare(rq, block, sdp->sector_size);

	} else if (rq_data_dir(rq) == READ) {
		SCpnt->cmnd[0] = READ_6;
		SCpnt->sc_data_direction = DMA_FROM_DEVICE;
	} else {
		scmd_printk(KERN_ERR, SCpnt, "Unknown command %x\n", rq->cmd_flags);
		goto out;
	}

	SCSI_LOG_HLQUEUE(2, scmd_printk(KERN_INFO, SCpnt,
					"%s %d/%u 512 byte blocks.\n",
					(rq_data_dir(rq) == WRITE) ?
					"writing" : "reading", this_count,
					blk_rq_sectors(rq)));

	/* Set RDPROTECT/WRPROTECT if disk is formatted with DIF */
	host_dif = scsi_host_dif_capable(sdp->host, sdkp->protection_type);
	if (host_dif)
		protect = 1 << 5;
	else
		protect = 0;

	if (host_dif == SD_DIF_TYPE2_PROTECTION) {
		SCpnt->cmnd = mempool_alloc(sd_cdb_pool, GFP_ATOMIC);

		if (unlikely(SCpnt->cmnd == NULL)) {
			ret = BLKPREP_DEFER;
			goto out;
		}

		SCpnt->cmd_len = SD_EXT_CDB_SIZE;
		memset(SCpnt->cmnd, 0, SCpnt->cmd_len);
		SCpnt->cmnd[0] = VARIABLE_LENGTH_CMD;
		SCpnt->cmnd[7] = 0x18;
		SCpnt->cmnd[9] = (rq_data_dir(rq) == READ) ? READ_32 : WRITE_32;
		SCpnt->cmnd[10] = protect | ((rq->cmd_flags & REQ_FUA) ? 0x8 : 0);

		/* LBA */
		SCpnt->cmnd[12] = sizeof(block) > 4 ? (unsigned char) (block >> 56) & 0xff : 0;
		SCpnt->cmnd[13] = sizeof(block) > 4 ? (unsigned char) (block >> 48) & 0xff : 0;
		SCpnt->cmnd[14] = sizeof(block) > 4 ? (unsigned char) (block >> 40) & 0xff : 0;
		SCpnt->cmnd[15] = sizeof(block) > 4 ? (unsigned char) (block >> 32) & 0xff : 0;
		SCpnt->cmnd[16] = (unsigned char) (block >> 24) & 0xff;
		SCpnt->cmnd[17] = (unsigned char) (block >> 16) & 0xff;
		SCpnt->cmnd[18] = (unsigned char) (block >> 8) & 0xff;
		SCpnt->cmnd[19] = (unsigned char) block & 0xff;

		/* Expected Indirect LBA */
		SCpnt->cmnd[20] = (unsigned char) (block >> 24) & 0xff;
		SCpnt->cmnd[21] = (unsigned char) (block >> 16) & 0xff;
		SCpnt->cmnd[22] = (unsigned char) (block >> 8) & 0xff;
		SCpnt->cmnd[23] = (unsigned char) block & 0xff;

		/* Transfer length */
		SCpnt->cmnd[28] = (unsigned char) (this_count >> 24) & 0xff;
		SCpnt->cmnd[29] = (unsigned char) (this_count >> 16) & 0xff;
		SCpnt->cmnd[30] = (unsigned char) (this_count >> 8) & 0xff;
		SCpnt->cmnd[31] = (unsigned char) this_count & 0xff;
	} else if (block > 0xffffffff) {
		SCpnt->cmnd[0] += READ_16 - READ_6;
		SCpnt->cmnd[1] = protect | ((rq->cmd_flags & REQ_FUA) ? 0x8 : 0);
		SCpnt->cmnd[2] = sizeof(block) > 4 ? (unsigned char) (block >> 56) & 0xff : 0;
		SCpnt->cmnd[3] = sizeof(block) > 4 ? (unsigned char) (block >> 48) & 0xff : 0;
		SCpnt->cmnd[4] = sizeof(block) > 4 ? (unsigned char) (block >> 40) & 0xff : 0;
		SCpnt->cmnd[5] = sizeof(block) > 4 ? (unsigned char) (block >> 32) & 0xff : 0;
		SCpnt->cmnd[6] = (unsigned char) (block >> 24) & 0xff;
		SCpnt->cmnd[7] = (unsigned char) (block >> 16) & 0xff;
		SCpnt->cmnd[8] = (unsigned char) (block >> 8) & 0xff;
		SCpnt->cmnd[9] = (unsigned char) block & 0xff;
		SCpnt->cmnd[10] = (unsigned char) (this_count >> 24) & 0xff;
		SCpnt->cmnd[11] = (unsigned char) (this_count >> 16) & 0xff;
		SCpnt->cmnd[12] = (unsigned char) (this_count >> 8) & 0xff;
		SCpnt->cmnd[13] = (unsigned char) this_count & 0xff;
		SCpnt->cmnd[14] = SCpnt->cmnd[15] = 0;
	} else if ((this_count > 0xff) || (block > 0x1fffff) ||
		   scsi_device_protection(SCpnt->device) ||
		   SCpnt->device->use_10_for_rw) {
		if (this_count > 0xffff)
			this_count = 0xffff;

		SCpnt->cmnd[0] += READ_10 - READ_6;
		SCpnt->cmnd[1] = protect | ((rq->cmd_flags & REQ_FUA) ? 0x8 : 0);
		SCpnt->cmnd[2] = (unsigned char) (block >> 24) & 0xff;
		SCpnt->cmnd[3] = (unsigned char) (block >> 16) & 0xff;
		SCpnt->cmnd[4] = (unsigned char) (block >> 8) & 0xff;
		SCpnt->cmnd[5] = (unsigned char) block & 0xff;
		SCpnt->cmnd[6] = SCpnt->cmnd[9] = 0;
		SCpnt->cmnd[7] = (unsigned char) (this_count >> 8) & 0xff;
		SCpnt->cmnd[8] = (unsigned char) this_count & 0xff;
	} else {
		if (unlikely(rq->cmd_flags & REQ_FUA)) {
			/*
			 * This happens only if this drive failed
			 * 10byte rw command with ILLEGAL_REQUEST
			 * during operation and thus turned off
			 * use_10_for_rw.
			 */
			scmd_printk(KERN_ERR, SCpnt,
				    "FUA write on READ/WRITE(6) drive\n");
			goto out;
		}

		SCpnt->cmnd[1] |= (unsigned char) ((block >> 16) & 0x1f);
		SCpnt->cmnd[2] = (unsigned char) ((block >> 8) & 0xff);
		SCpnt->cmnd[3] = (unsigned char) block & 0xff;
		SCpnt->cmnd[4] = (unsigned char) this_count;
		SCpnt->cmnd[5] = 0;
	}
	SCpnt->sdb.length = this_count * sdp->sector_size;

	/* If DIF or DIX is enabled, tell HBA how to handle request */
	if (host_dif || scsi_prot_sg_count(SCpnt))
		sd_prot_op(SCpnt, host_dif);

	/*
	 * We shouldn't disconnect in the middle of a sector, so with a dumb
	 * host adapter, it's safe to assume that we can at least transfer
	 * this many bytes between each connect / disconnect.
	 */
	SCpnt->transfersize = sdp->sector_size;
	SCpnt->underflow = this_count << 9;
	SCpnt->allowed = SD_MAX_RETRIES;

	/*
	 * This indicates that the command is ready from our end to be
	 * queued.
	 */
	ret = BLKPREP_OK;
 out:
	return scsi_prep_return(q, rq, ret);
}