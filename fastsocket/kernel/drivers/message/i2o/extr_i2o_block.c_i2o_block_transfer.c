#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct request {int /*<<< orphan*/  q; struct i2o_block_request* special; TYPE_1__* rq_disk; } ;
struct TYPE_10__ {void* tcntxt; void* icntxt; } ;
struct TYPE_11__ {int* head; TYPE_4__ s; } ;
struct i2o_message {int* body; TYPE_5__ u; } ;
struct i2o_controller {scalar_t__ adaptec; } ;
struct i2o_block_request {int /*<<< orphan*/  queue; } ;
struct i2o_block_device {int rcache; int wcache; int /*<<< orphan*/  open_queue_depth; int /*<<< orphan*/  open_queue; TYPE_3__* i2o_dev; } ;
struct TYPE_12__ {int context; } ;
struct TYPE_8__ {int tid; } ;
struct TYPE_9__ {struct i2o_controller* iop; TYPE_2__ lct_data; } ;
struct TYPE_7__ {struct i2o_block_device* private_data; } ;

/* Variables and functions */
#define  CACHE_PREFETCH 133 
#define  CACHE_SMARTBACK 132 
#define  CACHE_SMARTFETCH 131 
#define  CACHE_SMARTTHROUGH 130 
#define  CACHE_WRITEBACK 129 
#define  CACHE_WRITETHROUGH 128 
 int ENODEV ; 
 int ENOMEM ; 
 int HOST_TID ; 
 int I2O_CMD_BLOCK_READ ; 
 int I2O_CMD_BLOCK_WRITE ; 
 int I2O_CMD_PRIVATE ; 
 int I2O_CMD_SCSI_EXEC ; 
 int I2O_MESSAGE_SIZE (int) ; 
 int I2O_VENDOR_DPT ; 
 scalar_t__ IS_ERR (struct i2o_message*) ; 
 int KERNEL_SECTOR_SHIFT ; 
 int PTR_ERR (struct i2o_message*) ; 
 scalar_t__ READ ; 
 int /*<<< orphan*/  READ_10 ; 
 int SGL_OFFSET_12 ; 
 int SGL_OFFSET_8 ; 
 int /*<<< orphan*/  WRITE_10 ; 
 int blk_rq_bytes (struct request*) ; 
 int blk_rq_pos (struct request*) ; 
 int blk_rq_sectors (struct request*) ; 
 int cpu_to_be16 (int) ; 
 int cpu_to_be32 (int) ; 
 void* cpu_to_le32 (int) ; 
 TYPE_6__ i2o_block_driver ; 
 int /*<<< orphan*/  i2o_block_sglist_alloc (struct i2o_controller*,struct i2o_block_request*,int**) ; 
 int i2o_cntxt_list_add (struct i2o_controller*,struct request*) ; 
 int /*<<< orphan*/  i2o_cntxt_list_remove (struct i2o_controller*,struct request*) ; 
 struct i2o_message* i2o_msg_get (struct i2o_controller*) ; 
 int /*<<< orphan*/  i2o_msg_nop (struct i2o_controller*,struct i2o_message*) ; 
 int /*<<< orphan*/  i2o_msg_post (struct i2o_controller*,struct i2o_message*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  osm_err (char*) ; 
 int queue_logical_block_size (int /*<<< orphan*/ ) ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int i2o_block_transfer(struct request *req)
{
	struct i2o_block_device *dev = req->rq_disk->private_data;
	struct i2o_controller *c;
	u32 tid = dev->i2o_dev->lct_data.tid;
	struct i2o_message *msg;
	u32 *mptr;
	struct i2o_block_request *ireq = req->special;
	u32 tcntxt;
	u32 sgl_offset = SGL_OFFSET_8;
	u32 ctl_flags = 0x00000000;
	int rc;
	u32 cmd;

	if (unlikely(!dev->i2o_dev)) {
		osm_err("transfer to removed drive\n");
		rc = -ENODEV;
		goto exit;
	}

	c = dev->i2o_dev->iop;

	msg = i2o_msg_get(c);
	if (IS_ERR(msg)) {
		rc = PTR_ERR(msg);
		goto exit;
	}

	tcntxt = i2o_cntxt_list_add(c, req);
	if (!tcntxt) {
		rc = -ENOMEM;
		goto nop_msg;
	}

	msg->u.s.icntxt = cpu_to_le32(i2o_block_driver.context);
	msg->u.s.tcntxt = cpu_to_le32(tcntxt);

	mptr = &msg->body[0];

	if (rq_data_dir(req) == READ) {
		cmd = I2O_CMD_BLOCK_READ << 24;

		switch (dev->rcache) {
		case CACHE_PREFETCH:
			ctl_flags = 0x201F0008;
			break;

		case CACHE_SMARTFETCH:
			if (blk_rq_sectors(req) > 16)
				ctl_flags = 0x201F0008;
			else
				ctl_flags = 0x001F0000;
			break;

		default:
			break;
		}
	} else {
		cmd = I2O_CMD_BLOCK_WRITE << 24;

		switch (dev->wcache) {
		case CACHE_WRITETHROUGH:
			ctl_flags = 0x001F0008;
			break;
		case CACHE_WRITEBACK:
			ctl_flags = 0x001F0010;
			break;
		case CACHE_SMARTBACK:
			if (blk_rq_sectors(req) > 16)
				ctl_flags = 0x001F0004;
			else
				ctl_flags = 0x001F0010;
			break;
		case CACHE_SMARTTHROUGH:
			if (blk_rq_sectors(req) > 16)
				ctl_flags = 0x001F0004;
			else
				ctl_flags = 0x001F0010;
		default:
			break;
		}
	}

#ifdef CONFIG_I2O_EXT_ADAPTEC
	if (c->adaptec) {
		u8 cmd[10];
		u32 scsi_flags;
		u16 hwsec;

		hwsec = queue_logical_block_size(req->q) >> KERNEL_SECTOR_SHIFT;
		memset(cmd, 0, 10);

		sgl_offset = SGL_OFFSET_12;

		msg->u.head[1] =
		    cpu_to_le32(I2O_CMD_PRIVATE << 24 | HOST_TID << 12 | tid);

		*mptr++ = cpu_to_le32(I2O_VENDOR_DPT << 16 | I2O_CMD_SCSI_EXEC);
		*mptr++ = cpu_to_le32(tid);

		/*
		 * ENABLE_DISCONNECT
		 * SIMPLE_TAG
		 * RETURN_SENSE_DATA_IN_REPLY_MESSAGE_FRAME
		 */
		if (rq_data_dir(req) == READ) {
			cmd[0] = READ_10;
			scsi_flags = 0x60a0000a;
		} else {
			cmd[0] = WRITE_10;
			scsi_flags = 0xa0a0000a;
		}

		*mptr++ = cpu_to_le32(scsi_flags);

		*((u32 *) & cmd[2]) = cpu_to_be32(blk_rq_pos(req) * hwsec);
		*((u16 *) & cmd[7]) = cpu_to_be16(blk_rq_sectors(req) * hwsec);

		memcpy(mptr, cmd, 10);
		mptr += 4;
		*mptr++ = cpu_to_le32(blk_rq_bytes(req));
	} else
#endif
	{
		msg->u.head[1] = cpu_to_le32(cmd | HOST_TID << 12 | tid);
		*mptr++ = cpu_to_le32(ctl_flags);
		*mptr++ = cpu_to_le32(blk_rq_bytes(req));
		*mptr++ =
		    cpu_to_le32((u32) (blk_rq_pos(req) << KERNEL_SECTOR_SHIFT));
		*mptr++ =
		    cpu_to_le32(blk_rq_pos(req) >> (32 - KERNEL_SECTOR_SHIFT));
	}

	if (!i2o_block_sglist_alloc(c, ireq, &mptr)) {
		rc = -ENOMEM;
		goto context_remove;
	}

	msg->u.head[0] =
	    cpu_to_le32(I2O_MESSAGE_SIZE(mptr - &msg->u.head[0]) | sgl_offset);

	list_add_tail(&ireq->queue, &dev->open_queue);
	dev->open_queue_depth++;

	i2o_msg_post(c, msg);

	return 0;

      context_remove:
	i2o_cntxt_list_remove(c, req);

      nop_msg:
	i2o_msg_nop(c, msg);

      exit:
	return rc;
}