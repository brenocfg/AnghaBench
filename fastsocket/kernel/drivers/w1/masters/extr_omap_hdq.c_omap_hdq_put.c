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
struct hdq_data {scalar_t__ hdq_usecount; int /*<<< orphan*/  hdq_mutex; int /*<<< orphan*/  hdq_fck; int /*<<< orphan*/  hdq_ick; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINTR ; 
 int EINVAL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omap_hdq_put(struct hdq_data *hdq_data)
{
	int ret = 0;

	ret = mutex_lock_interruptible(&hdq_data->hdq_mutex);
	if (ret < 0)
		return -EINTR;

	if (0 == hdq_data->hdq_usecount) {
		dev_dbg(hdq_data->dev, "attempt to decrement use count"
			"when it is zero");
		ret = -EINVAL;
	} else {
		hdq_data->hdq_usecount--;
		module_put(THIS_MODULE);
		if (0 == hdq_data->hdq_usecount) {
			clk_disable(hdq_data->hdq_ick);
			clk_disable(hdq_data->hdq_fck);
		}
	}
	mutex_unlock(&hdq_data->hdq_mutex);

	return ret;
}