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
typedef  int /*<<< orphan*/  u8 ;
struct hdq_data {scalar_t__ init_trans; int /*<<< orphan*/  hdq_mutex; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int hdq_write_byte (struct hdq_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_hdq_get (struct hdq_data*) ; 
 int /*<<< orphan*/  omap_hdq_put (struct hdq_data*) ; 

__attribute__((used)) static void omap_w1_write_byte(void *_hdq, u8 byte)
{
	struct hdq_data *hdq_data = _hdq;
	int ret;
	u8 status;

	/* First write to initialize the transfer */
	if (hdq_data->init_trans == 0)
		omap_hdq_get(hdq_data);

	ret = mutex_lock_interruptible(&hdq_data->hdq_mutex);
	if (ret < 0) {
		dev_dbg(hdq_data->dev, "Could not acquire mutex\n");
		return;
	}
	hdq_data->init_trans++;
	mutex_unlock(&hdq_data->hdq_mutex);

	ret = hdq_write_byte(hdq_data, byte, &status);
	if (ret == 0) {
		dev_dbg(hdq_data->dev, "TX failure:Ctrl status %x\n", status);
		return;
	}

	/* Second write, data transfered. Release the module */
	if (hdq_data->init_trans > 1) {
		omap_hdq_put(hdq_data);
		ret = mutex_lock_interruptible(&hdq_data->hdq_mutex);
		if (ret < 0) {
			dev_dbg(hdq_data->dev, "Could not acquire mutex\n");
			return;
		}
		hdq_data->init_trans = 0;
		mutex_unlock(&hdq_data->hdq_mutex);
	}

	return;
}