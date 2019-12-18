#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct mthca_mailbox {int* buf; int /*<<< orphan*/  dma; } ;
struct TYPE_9__ {int fw_start; int fw_end; } ;
struct TYPE_8__ {int fw_pages; int clr_int_base; int eq_arm_base; int eq_set_ci_base; } ;
struct TYPE_10__ {TYPE_4__ tavor; TYPE_3__ arbel; } ;
struct TYPE_7__ {int max_cmds; int* dbell_offsets; } ;
struct TYPE_6__ {int addr; int size; } ;
struct mthca_dev {int fw_ver; TYPE_5__ fw; TYPE_2__ cmd; TYPE_1__ catas_err; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  CMD_QUERY_FW ; 
 int /*<<< orphan*/  CMD_TIME_CLASS_A ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mthca_mailbox*) ; 
 int MTHCA_CMD_NUM_DBELL_DWORDS ; 
 int /*<<< orphan*/  MTHCA_GET (int,int*,scalar_t__) ; 
 int MTHCA_ICM_PAGE_SHIFT ; 
 int MTHCA_ICM_PAGE_SIZE ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int PTR_ERR (struct mthca_mailbox*) ; 
 scalar_t__ QUERY_FW_CLR_INT_BASE_OFFSET ; 
 scalar_t__ QUERY_FW_CMD_DB_BASE ; 
 scalar_t__ QUERY_FW_CMD_DB_EN_OFFSET ; 
 scalar_t__ QUERY_FW_CMD_DB_OFFSET ; 
 scalar_t__ QUERY_FW_END_OFFSET ; 
 scalar_t__ QUERY_FW_EQ_ARM_BASE_OFFSET ; 
 scalar_t__ QUERY_FW_EQ_SET_CI_BASE_OFFSET ; 
 scalar_t__ QUERY_FW_ERR_SIZE_OFFSET ; 
 scalar_t__ QUERY_FW_ERR_START_OFFSET ; 
 scalar_t__ QUERY_FW_MAX_CMD_OFFSET ; 
 scalar_t__ QUERY_FW_SIZE_OFFSET ; 
 scalar_t__ QUERY_FW_START_OFFSET ; 
 scalar_t__ QUERY_FW_VER_OFFSET ; 
 struct mthca_mailbox* mthca_alloc_mailbox (struct mthca_dev*,int /*<<< orphan*/ ) ; 
 int mthca_cmd_box (struct mthca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_dbg (struct mthca_dev*,char*,...) ; 
 int /*<<< orphan*/  mthca_free_mailbox (struct mthca_dev*,struct mthca_mailbox*) ; 
 scalar_t__ mthca_is_memfree (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_setup_cmd_doorbells (struct mthca_dev*,int) ; 

int mthca_QUERY_FW(struct mthca_dev *dev)
{
	struct mthca_mailbox *mailbox;
	u32 *outbox;
	u64 base;
	u32 tmp;
	int err = 0;
	u8 lg;
	int i;

#define QUERY_FW_OUT_SIZE             0x100
#define QUERY_FW_VER_OFFSET            0x00
#define QUERY_FW_MAX_CMD_OFFSET        0x0f
#define QUERY_FW_ERR_START_OFFSET      0x30
#define QUERY_FW_ERR_SIZE_OFFSET       0x38

#define QUERY_FW_CMD_DB_EN_OFFSET      0x10
#define QUERY_FW_CMD_DB_OFFSET         0x50
#define QUERY_FW_CMD_DB_BASE           0x60

#define QUERY_FW_START_OFFSET          0x20
#define QUERY_FW_END_OFFSET            0x28

#define QUERY_FW_SIZE_OFFSET           0x00
#define QUERY_FW_CLR_INT_BASE_OFFSET   0x20
#define QUERY_FW_EQ_ARM_BASE_OFFSET    0x40
#define QUERY_FW_EQ_SET_CI_BASE_OFFSET 0x48

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);
	outbox = mailbox->buf;

	err = mthca_cmd_box(dev, 0, mailbox->dma, 0, 0, CMD_QUERY_FW,
			    CMD_TIME_CLASS_A);

	if (err)
		goto out;

	MTHCA_GET(dev->fw_ver,   outbox, QUERY_FW_VER_OFFSET);
	/*
	 * FW subminor version is at more significant bits than minor
	 * version, so swap here.
	 */
	dev->fw_ver = (dev->fw_ver & 0xffff00000000ull) |
		((dev->fw_ver & 0xffff0000ull) >> 16) |
		((dev->fw_ver & 0x0000ffffull) << 16);

	MTHCA_GET(lg, outbox, QUERY_FW_MAX_CMD_OFFSET);
	dev->cmd.max_cmds = 1 << lg;

	mthca_dbg(dev, "FW version %012llx, max commands %d\n",
		  (unsigned long long) dev->fw_ver, dev->cmd.max_cmds);

	MTHCA_GET(dev->catas_err.addr, outbox, QUERY_FW_ERR_START_OFFSET);
	MTHCA_GET(dev->catas_err.size, outbox, QUERY_FW_ERR_SIZE_OFFSET);

	mthca_dbg(dev, "Catastrophic error buffer at 0x%llx, size 0x%x\n",
		  (unsigned long long) dev->catas_err.addr, dev->catas_err.size);

	MTHCA_GET(tmp, outbox, QUERY_FW_CMD_DB_EN_OFFSET);
	if (tmp & 0x1) {
		mthca_dbg(dev, "FW supports commands through doorbells\n");

		MTHCA_GET(base, outbox, QUERY_FW_CMD_DB_BASE);
		for (i = 0; i < MTHCA_CMD_NUM_DBELL_DWORDS; ++i)
			MTHCA_GET(dev->cmd.dbell_offsets[i], outbox,
				  QUERY_FW_CMD_DB_OFFSET + (i << 1));

		mthca_setup_cmd_doorbells(dev, base);
	}

	if (mthca_is_memfree(dev)) {
		MTHCA_GET(dev->fw.arbel.fw_pages,       outbox, QUERY_FW_SIZE_OFFSET);
		MTHCA_GET(dev->fw.arbel.clr_int_base,   outbox, QUERY_FW_CLR_INT_BASE_OFFSET);
		MTHCA_GET(dev->fw.arbel.eq_arm_base,    outbox, QUERY_FW_EQ_ARM_BASE_OFFSET);
		MTHCA_GET(dev->fw.arbel.eq_set_ci_base, outbox, QUERY_FW_EQ_SET_CI_BASE_OFFSET);
		mthca_dbg(dev, "FW size %d KB\n", dev->fw.arbel.fw_pages << 2);

		/*
		 * Round up number of system pages needed in case
		 * MTHCA_ICM_PAGE_SIZE < PAGE_SIZE.
		 */
		dev->fw.arbel.fw_pages =
			ALIGN(dev->fw.arbel.fw_pages, PAGE_SIZE / MTHCA_ICM_PAGE_SIZE) >>
				(PAGE_SHIFT - MTHCA_ICM_PAGE_SHIFT);

		mthca_dbg(dev, "Clear int @ %llx, EQ arm @ %llx, EQ set CI @ %llx\n",
			  (unsigned long long) dev->fw.arbel.clr_int_base,
			  (unsigned long long) dev->fw.arbel.eq_arm_base,
			  (unsigned long long) dev->fw.arbel.eq_set_ci_base);
	} else {
		MTHCA_GET(dev->fw.tavor.fw_start, outbox, QUERY_FW_START_OFFSET);
		MTHCA_GET(dev->fw.tavor.fw_end,   outbox, QUERY_FW_END_OFFSET);

		mthca_dbg(dev, "FW size %d KB (start %llx, end %llx)\n",
			  (int) ((dev->fw.tavor.fw_end - dev->fw.tavor.fw_start) >> 10),
			  (unsigned long long) dev->fw.tavor.fw_start,
			  (unsigned long long) dev->fw.tavor.fw_end);
	}

out:
	mthca_free_mailbox(dev, mailbox);
	return err;
}