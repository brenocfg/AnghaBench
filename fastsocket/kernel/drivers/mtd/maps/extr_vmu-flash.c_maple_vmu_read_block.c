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
struct vmu_cache {int valid; unsigned char* buffer; unsigned int block; int /*<<< orphan*/  jiffies_atc; } ;
struct mtd_info {struct mdev_part* priv; } ;
struct memcard {int blocklen; int readcnt; unsigned char* blockread; TYPE_1__* parts; } ;
struct mdev_part {int partition; struct maple_device* mdev; } ;
struct maple_device {int /*<<< orphan*/  unit; int /*<<< orphan*/  port; int /*<<< orphan*/  dev; TYPE_2__* mq; int /*<<< orphan*/  busy; int /*<<< orphan*/  maple_wait; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {unsigned char* sendbuf; int /*<<< orphan*/  list; } ;
struct TYPE_3__ {struct vmu_cache* pcache; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int ENOMEM ; 
 int ENXIO ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  MAPLE_COMMAND_BREAD ; 
 int /*<<< orphan*/  MAPLE_FUNC_MEMCARD ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int maple_add_packet (struct maple_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct memcard* maple_get_drvdata (struct maple_device*) ; 
 int /*<<< orphan*/  maple_getcond_callback (struct maple_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  vmu_blockread ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int maple_vmu_read_block(unsigned int num, unsigned char *buf,
	struct mtd_info *mtd)
{
	struct memcard *card;
	struct mdev_part *mpart;
	struct maple_device *mdev;
	int partition, error = 0, x, wait;
	unsigned char *blockread = NULL;
	struct vmu_cache *pcache;
	__be32 sendbuf;

	mpart = mtd->priv;
	mdev = mpart->mdev;
	partition = mpart->partition;
	card = maple_get_drvdata(mdev);
	pcache = card->parts[partition].pcache;
	pcache->valid = 0;

	/* prepare the cache for this block */
	if (!pcache->buffer) {
		pcache->buffer = kmalloc(card->blocklen, GFP_KERNEL);
		if (!pcache->buffer) {
			dev_err(&mdev->dev, "VMU at (%d, %d) - read fails due"
				" to lack of memory\n", mdev->port,
				mdev->unit);
			error = -ENOMEM;
			goto outB;
		}
	}

	/*
	* Reads may be phased - again the hardware spec
	* supports this - though may not be any devices in
	* the wild that implement it, but we will here
	*/
	for (x = 0; x < card->readcnt; x++) {
		sendbuf = cpu_to_be32(partition << 24 | x << 16 | num);

		if (atomic_read(&mdev->busy) == 1) {
			wait_event_interruptible_timeout(mdev->maple_wait,
				atomic_read(&mdev->busy) == 0, HZ);
			if (atomic_read(&mdev->busy) == 1) {
				dev_notice(&mdev->dev, "VMU at (%d, %d)"
					" is busy\n", mdev->port, mdev->unit);
				error = -EAGAIN;
				goto outB;
			}
		}

		atomic_set(&mdev->busy, 1);
		blockread = kmalloc(card->blocklen/card->readcnt, GFP_KERNEL);
		if (!blockread) {
			error = -ENOMEM;
			atomic_set(&mdev->busy, 0);
			goto outB;
		}
		card->blockread = blockread;

		maple_getcond_callback(mdev, vmu_blockread, 0,
			MAPLE_FUNC_MEMCARD);
		error = maple_add_packet(mdev, MAPLE_FUNC_MEMCARD,
				MAPLE_COMMAND_BREAD, 2, &sendbuf);
		/* Very long timeouts seem to be needed when box is stressed */
		wait = wait_event_interruptible_timeout(mdev->maple_wait,
			(atomic_read(&mdev->busy) == 0 ||
			atomic_read(&mdev->busy) == 2), HZ * 3);
		/*
		* MTD layer does not handle hotplugging well
		* so have to return errors when VMU is unplugged
		* in the middle of a read (busy == 2)
		*/
		if (error || atomic_read(&mdev->busy) == 2) {
			if (atomic_read(&mdev->busy) == 2)
				error = -ENXIO;
			atomic_set(&mdev->busy, 0);
			card->blockread = NULL;
			goto outA;
		}
		if (wait == 0 || wait == -ERESTARTSYS) {
			card->blockread = NULL;
			atomic_set(&mdev->busy, 0);
			error = -EIO;
			list_del_init(&(mdev->mq->list));
			kfree(mdev->mq->sendbuf);
			mdev->mq->sendbuf = NULL;
			if (wait == -ERESTARTSYS) {
				dev_warn(&mdev->dev, "VMU read on (%d, %d)"
					" interrupted on block 0x%X\n",
					mdev->port, mdev->unit, num);
			} else
				dev_notice(&mdev->dev, "VMU read on (%d, %d)"
					" timed out on block 0x%X\n",
					mdev->port, mdev->unit, num);
			goto outA;
		}

		memcpy(buf + (card->blocklen/card->readcnt) * x, blockread,
			card->blocklen/card->readcnt);

		memcpy(pcache->buffer + (card->blocklen/card->readcnt) * x,
			card->blockread, card->blocklen/card->readcnt);
		card->blockread = NULL;
		pcache->block = num;
		pcache->jiffies_atc = jiffies;
		pcache->valid = 1;
		kfree(blockread);
	}

	return error;

outA:
	kfree(blockread);
outB:
	return error;
}