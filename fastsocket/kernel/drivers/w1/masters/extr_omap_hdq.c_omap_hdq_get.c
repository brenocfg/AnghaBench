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
struct hdq_data {int hdq_usecount; int /*<<< orphan*/  hdq_mutex; int /*<<< orphan*/  hdq_fck; int /*<<< orphan*/  hdq_ick; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINTR ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  OMAP_HDQ_CTRL_STATUS ; 
 int OMAP_HDQ_CTRL_STATUS_CLOCKENABLE ; 
 int OMAP_HDQ_CTRL_STATUS_INTERRUPTMASK ; 
 int /*<<< orphan*/  OMAP_HDQ_INT_STATUS ; 
 int OMAP_HDQ_MAX_USER ; 
 int /*<<< orphan*/  OMAP_HDQ_SYSCONFIG ; 
 int OMAP_HDQ_SYSCONFIG_AUTOIDLE ; 
 int /*<<< orphan*/  OMAP_HDQ_SYSSTATUS ; 
 int OMAP_HDQ_SYSSTATUS_RESETDONE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int _omap_hdq_reset (struct hdq_data*) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int hdq_reg_in (struct hdq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdq_reg_out (struct hdq_data*,int /*<<< orphan*/ ,int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_hdq_get(struct hdq_data *hdq_data)
{
	int ret = 0;

	ret = mutex_lock_interruptible(&hdq_data->hdq_mutex);
	if (ret < 0) {
		ret = -EINTR;
		goto rtn;
	}

	if (OMAP_HDQ_MAX_USER == hdq_data->hdq_usecount) {
		dev_dbg(hdq_data->dev, "attempt to exceed the max use count");
		ret = -EINVAL;
		goto out;
	} else {
		hdq_data->hdq_usecount++;
		try_module_get(THIS_MODULE);
		if (1 == hdq_data->hdq_usecount) {
			if (clk_enable(hdq_data->hdq_ick)) {
				dev_dbg(hdq_data->dev, "Can not enable ick\n");
				ret = -ENODEV;
				goto clk_err;
			}
			if (clk_enable(hdq_data->hdq_fck)) {
				dev_dbg(hdq_data->dev, "Can not enable fck\n");
				clk_disable(hdq_data->hdq_ick);
				ret = -ENODEV;
				goto clk_err;
			}

			/* make sure HDQ is out of reset */
			if (!(hdq_reg_in(hdq_data, OMAP_HDQ_SYSSTATUS) &
				OMAP_HDQ_SYSSTATUS_RESETDONE)) {
				ret = _omap_hdq_reset(hdq_data);
				if (ret)
					/* back up the count */
					hdq_data->hdq_usecount--;
			} else {
				/* select HDQ mode & enable clocks */
				hdq_reg_out(hdq_data, OMAP_HDQ_CTRL_STATUS,
					OMAP_HDQ_CTRL_STATUS_CLOCKENABLE |
					OMAP_HDQ_CTRL_STATUS_INTERRUPTMASK);
				hdq_reg_out(hdq_data, OMAP_HDQ_SYSCONFIG,
					OMAP_HDQ_SYSCONFIG_AUTOIDLE);
				hdq_reg_in(hdq_data, OMAP_HDQ_INT_STATUS);
			}
		}
	}

clk_err:
	clk_put(hdq_data->hdq_ick);
	clk_put(hdq_data->hdq_fck);
out:
	mutex_unlock(&hdq_data->hdq_mutex);
rtn:
	return ret;
}