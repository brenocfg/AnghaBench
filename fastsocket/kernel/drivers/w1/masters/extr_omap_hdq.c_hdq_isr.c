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
struct hdq_data {int hdq_irqstatus; int /*<<< orphan*/  dev; int /*<<< orphan*/  hdq_spinlock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  OMAP_HDQ_INT_STATUS ; 
 int OMAP_HDQ_INT_STATUS_RXCOMPLETE ; 
 int OMAP_HDQ_INT_STATUS_TIMEOUT ; 
 int OMAP_HDQ_INT_STATUS_TXCOMPLETE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int hdq_reg_in (struct hdq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdq_wait_queue ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t hdq_isr(int irq, void *_hdq)
{
	struct hdq_data *hdq_data = _hdq;
	unsigned long irqflags;

	spin_lock_irqsave(&hdq_data->hdq_spinlock, irqflags);
	hdq_data->hdq_irqstatus = hdq_reg_in(hdq_data, OMAP_HDQ_INT_STATUS);
	spin_unlock_irqrestore(&hdq_data->hdq_spinlock, irqflags);
	dev_dbg(hdq_data->dev, "hdq_isr: %x", hdq_data->hdq_irqstatus);

	if (hdq_data->hdq_irqstatus &
		(OMAP_HDQ_INT_STATUS_TXCOMPLETE | OMAP_HDQ_INT_STATUS_RXCOMPLETE
		| OMAP_HDQ_INT_STATUS_TIMEOUT)) {
		/* wake up sleeping process */
		wake_up(&hdq_wait_queue);
	}

	return IRQ_HANDLED;
}