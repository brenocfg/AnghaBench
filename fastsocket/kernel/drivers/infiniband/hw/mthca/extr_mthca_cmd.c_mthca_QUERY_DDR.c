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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mthca_mailbox {int /*<<< orphan*/  dma; int /*<<< orphan*/ * buf; } ;
struct mthca_dev {int ddr_start; int ddr_end; int mthca_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_QUERY_DDR ; 
 int /*<<< orphan*/  CMD_TIME_CLASS_A ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mthca_mailbox*) ; 
 int MTHCA_FLAG_DDR_HIDDEN ; 
 int /*<<< orphan*/  MTHCA_GET (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct mthca_mailbox*) ; 
 int /*<<< orphan*/  QUERY_DDR_END_OFFSET ; 
 int QUERY_DDR_INFO_HIDDEN_FLAG ; 
 int /*<<< orphan*/  QUERY_DDR_INFO_OFFSET ; 
 int /*<<< orphan*/  QUERY_DDR_START_OFFSET ; 
 struct mthca_mailbox* mthca_alloc_mailbox (struct mthca_dev*,int /*<<< orphan*/ ) ; 
 int mthca_cmd_box (struct mthca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_dbg (struct mthca_dev*,char*,...) ; 
 int /*<<< orphan*/  mthca_free_mailbox (struct mthca_dev*,struct mthca_mailbox*) ; 
 int /*<<< orphan*/  mthca_info (struct mthca_dev*,char*,char*) ; 

int mthca_QUERY_DDR(struct mthca_dev *dev)
{
	struct mthca_mailbox *mailbox;
	u8 info;
	u32 *outbox;
	int err = 0;

#define QUERY_DDR_OUT_SIZE         0x100
#define QUERY_DDR_START_OFFSET     0x00
#define QUERY_DDR_END_OFFSET       0x08
#define QUERY_DDR_INFO_OFFSET      0x13

#define QUERY_DDR_INFO_HIDDEN_FLAG (1 << 4)
#define QUERY_DDR_INFO_ECC_MASK    0x3

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);
	outbox = mailbox->buf;

	err = mthca_cmd_box(dev, 0, mailbox->dma, 0, 0, CMD_QUERY_DDR,
			    CMD_TIME_CLASS_A);

	if (err)
		goto out;

	MTHCA_GET(dev->ddr_start, outbox, QUERY_DDR_START_OFFSET);
	MTHCA_GET(dev->ddr_end,   outbox, QUERY_DDR_END_OFFSET);
	MTHCA_GET(info,           outbox, QUERY_DDR_INFO_OFFSET);

	if (!!(info & QUERY_DDR_INFO_HIDDEN_FLAG) !=
	    !!(dev->mthca_flags & MTHCA_FLAG_DDR_HIDDEN)) {
		mthca_info(dev, "FW reports that HCA-attached memory "
			   "is %s hidden; does not match PCI config\n",
			   (info & QUERY_DDR_INFO_HIDDEN_FLAG) ?
			   "" : "not");
	}
	if (info & QUERY_DDR_INFO_HIDDEN_FLAG)
		mthca_dbg(dev, "HCA-attached memory is hidden.\n");

	mthca_dbg(dev, "HCA memory size %d KB (start %llx, end %llx)\n",
		  (int) ((dev->ddr_end - dev->ddr_start) >> 10),
		  (unsigned long long) dev->ddr_start,
		  (unsigned long long) dev->ddr_end);

out:
	mthca_free_mailbox(dev, mailbox);
	return err;
}