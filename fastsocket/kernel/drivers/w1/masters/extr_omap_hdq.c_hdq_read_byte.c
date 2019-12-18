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
struct hdq_data {int hdq_irqstatus; int /*<<< orphan*/  hdq_mutex; int /*<<< orphan*/  dev; int /*<<< orphan*/  hdq_usecount; } ;

/* Variables and functions */
 int EINTR ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  OMAP_HDQ_CTRL_STATUS ; 
 int OMAP_HDQ_CTRL_STATUS_DIR ; 
 int OMAP_HDQ_CTRL_STATUS_GO ; 
 int OMAP_HDQ_INT_STATUS_RXCOMPLETE ; 
 int /*<<< orphan*/  OMAP_HDQ_RX_DATA ; 
 unsigned long OMAP_HDQ_TIMEOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int hdq_reg_in (struct hdq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdq_reg_merge (struct hdq_data*,int /*<<< orphan*/ ,int,int) ; 
 unsigned long jiffies ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int hdq_read_byte(struct hdq_data *hdq_data, u8 *val)
{
	int ret = 0;
	u8 status;
	unsigned long timeout = jiffies + OMAP_HDQ_TIMEOUT;

	ret = mutex_lock_interruptible(&hdq_data->hdq_mutex);
	if (ret < 0) {
		ret = -EINTR;
		goto rtn;
	}

	if (!hdq_data->hdq_usecount) {
		ret = -EINVAL;
		goto out;
	}

	if (!(hdq_data->hdq_irqstatus & OMAP_HDQ_INT_STATUS_RXCOMPLETE)) {
		hdq_reg_merge(hdq_data, OMAP_HDQ_CTRL_STATUS,
			OMAP_HDQ_CTRL_STATUS_DIR | OMAP_HDQ_CTRL_STATUS_GO,
			OMAP_HDQ_CTRL_STATUS_DIR | OMAP_HDQ_CTRL_STATUS_GO);
		/*
		 * The RX comes immediately after TX. It
		 * triggers another interrupt before we
		 * sleep. So we have to wait for RXCOMPLETE bit.
		 */
		while (!(hdq_data->hdq_irqstatus
			& OMAP_HDQ_INT_STATUS_RXCOMPLETE)
			&& time_before(jiffies, timeout)) {
			schedule_timeout_uninterruptible(1);
		}
		hdq_reg_merge(hdq_data, OMAP_HDQ_CTRL_STATUS, 0,
			OMAP_HDQ_CTRL_STATUS_DIR);
		status = hdq_data->hdq_irqstatus;
		/* check irqstatus */
		if (!(status & OMAP_HDQ_INT_STATUS_RXCOMPLETE)) {
			dev_dbg(hdq_data->dev, "timeout waiting for"
				"RXCOMPLETE, %x", status);
			ret = -ETIMEDOUT;
			goto out;
		}
	}
	/* the data is ready. Read it in! */
	*val = hdq_reg_in(hdq_data, OMAP_HDQ_RX_DATA);
out:
	mutex_unlock(&hdq_data->hdq_mutex);
rtn:
	return 0;

}