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
struct se_cmd {int t_task_lba; int t_data_nents; struct iblock_req* priv; TYPE_2__* se_dev; struct scatterlist* t_data_sg; } ;
struct scatterlist {int length; int /*<<< orphan*/  offset; } ;
struct iblock_req {int /*<<< orphan*/  pending; } ;
struct bio_list {int dummy; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
typedef  int sector_t ;
struct TYPE_3__ {int block_size; } ;
struct TYPE_4__ {TYPE_1__ dev_attrib; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IBLOCK_LBA_SHIFT ; 
 int /*<<< orphan*/  TCM_INVALID_CDB_FIELD ; 
 int /*<<< orphan*/  TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int bio_add_page (struct bio*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_list_add (struct bio_list*,struct bio*) ; 
 int /*<<< orphan*/  bio_list_init (struct bio_list*) ; 
 struct bio* bio_list_pop (struct bio_list*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 struct bio* iblock_get_bio (struct se_cmd*,int,int) ; 
 int /*<<< orphan*/  iblock_submit_bios (struct bio_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct iblock_req*) ; 
 struct iblock_req* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,int,int) ; 
 int sbc_get_write_same_sectors (struct se_cmd*) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 

__attribute__((used)) static sense_reason_t
iblock_execute_write_same(struct se_cmd *cmd)
{
	struct iblock_req *ibr;
	struct scatterlist *sg;
	struct bio *bio;
	struct bio_list list;
	sector_t block_lba = cmd->t_task_lba;
	sector_t sectors = sbc_get_write_same_sectors(cmd);

	sg = &cmd->t_data_sg[0];

	if (cmd->t_data_nents > 1 ||
	    sg->length != cmd->se_dev->dev_attrib.block_size) {
		pr_err("WRITE_SAME: Illegal SGL t_data_nents: %u length: %u"
			" block_size: %u\n", cmd->t_data_nents, sg->length,
			cmd->se_dev->dev_attrib.block_size);
		return TCM_INVALID_CDB_FIELD;
	}

	ibr = kzalloc(sizeof(struct iblock_req), GFP_KERNEL);
	if (!ibr)
		goto fail;
	cmd->priv = ibr;

	bio = iblock_get_bio(cmd, block_lba, 1);
	if (!bio)
		goto fail_free_ibr;

	bio_list_init(&list);
	bio_list_add(&list, bio);

	atomic_set(&ibr->pending, 1);

	while (sectors) {
		while (bio_add_page(bio, sg_page(sg), sg->length, sg->offset)
				!= sg->length) {

			bio = iblock_get_bio(cmd, block_lba, 1);
			if (!bio)
				goto fail_put_bios;

			atomic_inc(&ibr->pending);
			bio_list_add(&list, bio);
		}

		/* Always in 512 byte units for Linux/Block */
		block_lba += sg->length >> IBLOCK_LBA_SHIFT;
		sectors -= 1;
	}

	iblock_submit_bios(&list, WRITE);
	return 0;

fail_put_bios:
	while ((bio = bio_list_pop(&list)))
		bio_put(bio);
fail_free_ibr:
	kfree(ibr);
fail:
	return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
}