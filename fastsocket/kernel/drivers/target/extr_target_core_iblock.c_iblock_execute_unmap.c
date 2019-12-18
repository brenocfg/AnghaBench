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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int max_unmap_block_desc_count; int /*<<< orphan*/  max_unmap_lba_count; } ;
struct se_device {TYPE_2__* transport; TYPE_1__ dev_attrib; } ;
struct se_cmd {int data_length; scalar_t__* t_task_cdb; struct se_device* se_dev; } ;
struct iblock_dev {int /*<<< orphan*/  ibd_bd; } ;
typedef  scalar_t__ sense_reason_t ;
typedef  scalar_t__ sector_t ;
struct TYPE_4__ {scalar_t__ (* get_blocks ) (struct se_device*) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GOOD ; 
 struct iblock_dev* IBLOCK_DEV (struct se_device*) ; 
 int /*<<< orphan*/  SAM_STAT_GOOD ; 
 scalar_t__ TCM_ADDRESS_OUT_OF_RANGE ; 
 scalar_t__ TCM_INVALID_CDB_FIELD ; 
 scalar_t__ TCM_INVALID_PARAMETER_LIST ; 
 scalar_t__ TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE ; 
 scalar_t__ TCM_PARAMETER_LIST_LENGTH_ERROR ; 
 int blkdev_issue_discard (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_unaligned_be16 (unsigned char*) ; 
 int /*<<< orphan*/  get_unaligned_be32 (unsigned char*) ; 
 scalar_t__ get_unaligned_be64 (unsigned char*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long long,int,...) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int,...) ; 
 scalar_t__ stub1 (struct se_device*) ; 
 int /*<<< orphan*/  target_complete_cmd (struct se_cmd*,int /*<<< orphan*/ ) ; 
 unsigned char* transport_kmap_data_sg (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_kunmap_data_sg (struct se_cmd*) ; 

__attribute__((used)) static sense_reason_t
iblock_execute_unmap(struct se_cmd *cmd)
{
	struct se_device *dev = cmd->se_dev;
	struct iblock_dev *ib_dev = IBLOCK_DEV(dev);
	unsigned char *buf, *ptr = NULL;
	sector_t lba;
	int size;
	u32 range;
	sense_reason_t ret = 0;
	int dl, bd_dl, err;

	/* We never set ANC_SUP */
	if (cmd->t_task_cdb[1])
		return TCM_INVALID_CDB_FIELD;

	if (cmd->data_length == 0) {
		target_complete_cmd(cmd, SAM_STAT_GOOD);
		return 0;
	}

	if (cmd->data_length < 8) {
		pr_warn("UNMAP parameter list length %u too small\n",
			cmd->data_length);
		return TCM_PARAMETER_LIST_LENGTH_ERROR;
	}

	buf = transport_kmap_data_sg(cmd);
	if (!buf)
		return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	dl = get_unaligned_be16(&buf[0]);
	bd_dl = get_unaligned_be16(&buf[2]);

	size = cmd->data_length - 8;
	if (bd_dl > size)
		pr_warn("UNMAP parameter list length %u too small, ignoring bd_dl %u\n",
			cmd->data_length, bd_dl);
	else
		size = bd_dl;

	if (size / 16 > dev->dev_attrib.max_unmap_block_desc_count) {
		ret = TCM_INVALID_PARAMETER_LIST;
		goto err;
	}

	/* First UNMAP block descriptor starts at 8 byte offset */
	ptr = &buf[8];
	pr_debug("UNMAP: Sub: %s Using dl: %u bd_dl: %u size: %u"
		" ptr: %p\n", dev->transport->name, dl, bd_dl, size, ptr);

	while (size >= 16) {
		lba = get_unaligned_be64(&ptr[0]);
		range = get_unaligned_be32(&ptr[8]);
		pr_debug("UNMAP: Using lba: %llu and range: %u\n",
				 (unsigned long long)lba, range);

		if (range > dev->dev_attrib.max_unmap_lba_count) {
			ret = TCM_INVALID_PARAMETER_LIST;
			goto err;
		}

		if (lba + range > dev->transport->get_blocks(dev) + 1) {
			ret = TCM_ADDRESS_OUT_OF_RANGE;
			goto err;
		}

		err = blkdev_issue_discard(ib_dev->ibd_bd, lba, range,
					   GFP_KERNEL, 0);
		if (err < 0) {
			pr_err("blkdev_issue_discard() failed: %d\n",
					err);
			ret = TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
			goto err;
		}

		ptr += 16;
		size -= 16;
	}

err:
	transport_kunmap_data_sg(cmd);
	if (!ret)
		target_complete_cmd(cmd, GOOD);
	return ret;
}