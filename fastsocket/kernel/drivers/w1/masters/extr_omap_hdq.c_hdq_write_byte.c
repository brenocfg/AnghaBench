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
struct hdq_data {int hdq_irqstatus; int /*<<< orphan*/  dev; int /*<<< orphan*/  hdq_spinlock; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  OMAP_HDQ_CTRL_STATUS ; 
 int OMAP_HDQ_CTRL_STATUS_DIR ; 
 int OMAP_HDQ_CTRL_STATUS_GO ; 
 int /*<<< orphan*/  OMAP_HDQ_FLAG_CLEAR ; 
 int /*<<< orphan*/  OMAP_HDQ_INT_STATUS ; 
 int OMAP_HDQ_INT_STATUS_TXCOMPLETE ; 
 int /*<<< orphan*/  OMAP_HDQ_TIMEOUT ; 
 int /*<<< orphan*/  OMAP_HDQ_TX_DATA ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hdq_reg_in (struct hdq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdq_reg_merge (struct hdq_data*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  hdq_reg_out (struct hdq_data*,int /*<<< orphan*/ ,int) ; 
 int hdq_wait_for_flag (struct hdq_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  hdq_wait_queue ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdq_write_byte(struct hdq_data *hdq_data, u8 val, u8 *status)
{
	int ret;
	u8 tmp_status;
	unsigned long irqflags;

	*status = 0;

	spin_lock_irqsave(&hdq_data->hdq_spinlock, irqflags);
	/* clear interrupt flags via a dummy read */
	hdq_reg_in(hdq_data, OMAP_HDQ_INT_STATUS);
	/* ISR loads it with new INT_STATUS */
	hdq_data->hdq_irqstatus = 0;
	spin_unlock_irqrestore(&hdq_data->hdq_spinlock, irqflags);

	hdq_reg_out(hdq_data, OMAP_HDQ_TX_DATA, val);

	/* set the GO bit */
	hdq_reg_merge(hdq_data, OMAP_HDQ_CTRL_STATUS, OMAP_HDQ_CTRL_STATUS_GO,
		OMAP_HDQ_CTRL_STATUS_DIR | OMAP_HDQ_CTRL_STATUS_GO);
	/* wait for the TXCOMPLETE bit */
	ret = wait_event_timeout(hdq_wait_queue,
		hdq_data->hdq_irqstatus, OMAP_HDQ_TIMEOUT);
	if (ret == 0) {
		dev_dbg(hdq_data->dev, "TX wait elapsed\n");
		goto out;
	}

	*status = hdq_data->hdq_irqstatus;
	/* check irqstatus */
	if (!(*status & OMAP_HDQ_INT_STATUS_TXCOMPLETE)) {
		dev_dbg(hdq_data->dev, "timeout waiting for"
			"TXCOMPLETE/RXCOMPLETE, %x", *status);
		ret = -ETIMEDOUT;
		goto out;
	}

	/* wait for the GO bit return to zero */
	ret = hdq_wait_for_flag(hdq_data, OMAP_HDQ_CTRL_STATUS,
			OMAP_HDQ_CTRL_STATUS_GO,
			OMAP_HDQ_FLAG_CLEAR, &tmp_status);
	if (ret) {
		dev_dbg(hdq_data->dev, "timeout waiting GO bit"
			"return to zero, %x", tmp_status);
	}

out:
	return ret;
}