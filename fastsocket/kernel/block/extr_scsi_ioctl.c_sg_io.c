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
struct sg_iovec {int dummy; } ;
struct sg_io_hdr {char interface_id; scalar_t__ cmd_len; int dxfer_len; int dxfer_direction; int iovec_count; int /*<<< orphan*/  duration; int /*<<< orphan*/  dxferp; } ;
struct request_queue {int dummy; } ;
struct request {char* sense; scalar_t__ retries; scalar_t__ sense_len; struct bio* bio; } ;
struct iovec {int dummy; } ;
struct gendisk {int dummy; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  sense ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 scalar_t__ BLK_MAX_CDB ; 
 int EFAULT ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  READ ; 
 int SCSI_SENSE_BUFFERSIZE ; 
#define  SG_DXFER_FROM_DEV 130 
#define  SG_DXFER_TO_DEV 129 
#define  SG_DXFER_TO_FROM_DEV 128 
 int /*<<< orphan*/  WRITE ; 
 int blk_complete_sghdr_rq (struct request*,struct sg_io_hdr*,struct bio*) ; 
 int /*<<< orphan*/  blk_execute_rq (struct request_queue*,struct gendisk*,struct request*,int /*<<< orphan*/ ) ; 
 scalar_t__ blk_fill_sghdr_rq (struct request_queue*,struct request*,struct sg_io_hdr*,int /*<<< orphan*/ ) ; 
 struct request* blk_get_request (struct request_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 int blk_rq_map_user (struct request_queue*,struct request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int blk_rq_map_user_iov (struct request_queue*,struct request*,int /*<<< orphan*/ *,struct sg_iovec*,int,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ copy_from_user (struct sg_iovec*,int /*<<< orphan*/ ,int const) ; 
 size_t iov_length (struct iovec*,int) ; 
 int iov_shorten (struct iovec*,int,size_t) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (unsigned long) ; 
 int /*<<< orphan*/  kfree (struct sg_iovec*) ; 
 struct sg_iovec* kmalloc (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int queue_max_hw_sectors (struct request_queue*) ; 

__attribute__((used)) static int sg_io(struct request_queue *q, struct gendisk *bd_disk,
		struct sg_io_hdr *hdr, fmode_t mode)
{
	unsigned long start_time;
	int writing = 0, ret = 0;
	struct request *rq;
	char sense[SCSI_SENSE_BUFFERSIZE];
	struct bio *bio;

	if (hdr->interface_id != 'S')
		return -EINVAL;
	if (hdr->cmd_len > BLK_MAX_CDB)
		return -EINVAL;

	if (hdr->dxfer_len > (queue_max_hw_sectors(q) << 9))
		return -EIO;

	if (hdr->dxfer_len)
		switch (hdr->dxfer_direction) {
		default:
			return -EINVAL;
		case SG_DXFER_TO_DEV:
			writing = 1;
			break;
		case SG_DXFER_TO_FROM_DEV:
		case SG_DXFER_FROM_DEV:
			break;
		}

	rq = blk_get_request(q, writing ? WRITE : READ, GFP_KERNEL);
	if (!rq)
		return -ENODEV;

	if (blk_fill_sghdr_rq(q, rq, hdr, mode)) {
		blk_put_request(rq);
		return -EFAULT;
	}

	if (hdr->iovec_count) {
		const int size = sizeof(struct sg_iovec) * hdr->iovec_count;
		size_t iov_data_len;
		struct sg_iovec *iov;

		iov = kmalloc(size, GFP_KERNEL);
		if (!iov) {
			ret = -ENOMEM;
			goto out;
		}

		if (copy_from_user(iov, hdr->dxferp, size)) {
			kfree(iov);
			ret = -EFAULT;
			goto out;
		}

		/* SG_IO howto says that the shorter of the two wins */
		iov_data_len = iov_length((struct iovec *)iov,
					  hdr->iovec_count);
		if (hdr->dxfer_len < iov_data_len) {
			hdr->iovec_count = iov_shorten((struct iovec *)iov,
						       hdr->iovec_count,
						       hdr->dxfer_len);
			iov_data_len = hdr->dxfer_len;
		}

		ret = blk_rq_map_user_iov(q, rq, NULL, iov, hdr->iovec_count,
					  iov_data_len, GFP_KERNEL);
		kfree(iov);
	} else if (hdr->dxfer_len)
		ret = blk_rq_map_user(q, rq, NULL, hdr->dxferp, hdr->dxfer_len,
				      GFP_KERNEL);

	if (ret)
		goto out;

	bio = rq->bio;
	memset(sense, 0, sizeof(sense));
	rq->sense = sense;
	rq->sense_len = 0;
	rq->retries = 0;

	start_time = jiffies;

	/* ignore return value. All information is passed back to caller
	 * (if he doesn't check that is his problem).
	 * N.B. a non-zero SCSI status is _not_ necessarily an error.
	 */
	blk_execute_rq(q, bd_disk, rq, 0);

	hdr->duration = jiffies_to_msecs(jiffies - start_time);

	return blk_complete_sghdr_rq(rq, hdr, bio);
out:
	blk_put_request(rq);
	return ret;
}