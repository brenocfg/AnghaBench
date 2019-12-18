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
struct request_queue {int /*<<< orphan*/  queue_lock; } ;
struct request {scalar_t__ special; } ;
struct omap_mbox {TYPE_1__* rxq; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
typedef  scalar_t__ mbox_msg_t ;
struct TYPE_2__ {struct request_queue* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_end_request_all (struct request*,int /*<<< orphan*/ ) ; 
 struct request* blk_fetch_request (struct request_queue*) ; 
 struct omap_mbox* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mbox_seq_test (struct omap_mbox*,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,char,char,char,char) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
omap_mbox_read(struct device *dev, struct device_attribute *attr, char *buf)
{
	unsigned long flags;
	struct request *rq;
	mbox_msg_t *p = (mbox_msg_t *) buf;
	struct omap_mbox *mbox = dev_get_drvdata(dev);
	struct request_queue *q = mbox->rxq->queue;

	while (1) {
		spin_lock_irqsave(q->queue_lock, flags);
		rq = blk_fetch_request(q);
		spin_unlock_irqrestore(q->queue_lock, flags);

		if (!rq)
			break;

		*p = (mbox_msg_t)rq->special;

		blk_end_request_all(rq, 0);

		if (unlikely(mbox_seq_test(mbox, *p))) {
			pr_info("mbox: Illegal seq bit!(%08x) ignored\n", *p);
			continue;
		}
		p++;
	}

	pr_debug("%02x %02x %02x %02x\n", buf[0], buf[1], buf[2], buf[3]);

	return (size_t) ((char *)p - buf);
}