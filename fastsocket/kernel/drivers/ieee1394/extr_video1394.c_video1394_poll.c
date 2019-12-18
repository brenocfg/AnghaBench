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
struct file_ctx {TYPE_2__* ohci; struct dma_iso_ctx* current_ctx; } ;
struct file {struct file_ctx* private_data; } ;
struct dma_iso_ctx {int num_desc; scalar_t__* buffer_status; int /*<<< orphan*/  lock; int /*<<< orphan*/  waitq; } ;
typedef  int /*<<< orphan*/  poll_table ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 unsigned int POLLERR ; 
 unsigned int POLLIN ; 
 unsigned int POLLRDNORM ; 
 int /*<<< orphan*/  PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ VIDEO1394_BUFFER_READY ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned int video1394_poll(struct file *file, poll_table *pt)
{
	struct file_ctx *ctx;
	unsigned int mask = 0;
	unsigned long flags;
	struct dma_iso_ctx *d;
	int i;

	ctx = file->private_data;
	d = ctx->current_ctx;
	if (d == NULL) {
		PRINT(KERN_ERR, ctx->ohci->host->id,
				"Current iso context not set");
		return POLLERR;
	}

	poll_wait(file, &d->waitq, pt);

	spin_lock_irqsave(&d->lock, flags);
	for (i = 0; i < d->num_desc; i++) {
		if (d->buffer_status[i] == VIDEO1394_BUFFER_READY) {
			mask |= POLLIN | POLLRDNORM;
			break;
		}
	}
	spin_unlock_irqrestore(&d->lock, flags);

	return mask;
}