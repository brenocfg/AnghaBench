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
struct poll_table_struct {int dummy; } ;
struct file {int f_mode; scalar_t__ private_data; } ;
struct TYPE_4__ {int count; scalar_t__ dma_fragsize; scalar_t__ dmasize; scalar_t__ mapped; int /*<<< orphan*/  wait; int /*<<< orphan*/  ready; } ;
struct TYPE_3__ {int count; scalar_t__ dma_fragsize; int /*<<< orphan*/  wait; int /*<<< orphan*/  ready; } ;
struct au1550_state {int /*<<< orphan*/  lock; TYPE_2__ dma_dac; TYPE_1__ dma_adc; } ;

/* Variables and functions */
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 unsigned int POLLRDNORM ; 
 unsigned int POLLWRNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned int
au1550_poll(struct file *file, struct poll_table_struct *wait)
{
	struct au1550_state *s = (struct au1550_state *)file->private_data;
	unsigned long   flags;
	unsigned int    mask = 0;

	if (file->f_mode & FMODE_WRITE) {
		if (!s->dma_dac.ready)
			return 0;
		poll_wait(file, &s->dma_dac.wait, wait);
	}
	if (file->f_mode & FMODE_READ) {
		if (!s->dma_adc.ready)
			return 0;
		poll_wait(file, &s->dma_adc.wait, wait);
	}

	spin_lock_irqsave(&s->lock, flags);

	if (file->f_mode & FMODE_READ) {
		if (s->dma_adc.count >= (signed)s->dma_adc.dma_fragsize)
			mask |= POLLIN | POLLRDNORM;
	}
	if (file->f_mode & FMODE_WRITE) {
		if (s->dma_dac.mapped) {
			if (s->dma_dac.count >=
			    (signed)s->dma_dac.dma_fragsize)
				mask |= POLLOUT | POLLWRNORM;
		} else {
			if ((signed) s->dma_dac.dmasize >=
			    s->dma_dac.count + (signed)s->dma_dac.dma_fragsize)
				mask |= POLLOUT | POLLWRNORM;
		}
	}
	spin_unlock_irqrestore(&s->lock, flags);
	return mask;
}