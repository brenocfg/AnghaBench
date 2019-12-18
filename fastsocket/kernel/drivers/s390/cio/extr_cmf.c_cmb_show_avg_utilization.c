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
typedef  unsigned long u64 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cmbdata {unsigned long device_connect_time; unsigned long function_pending_time; unsigned long device_disconnect_time; unsigned long elapsed_time; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EAGAIN ; 
 int ENODEV ; 
 int cmf_readall (int /*<<< orphan*/ ,struct cmbdata*) ; 
 int sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  to_ccwdev (struct device*) ; 

__attribute__((used)) static ssize_t cmb_show_avg_utilization(struct device *dev,
					struct device_attribute *attr,
					char *buf)
{
	struct cmbdata data;
	u64 utilization;
	unsigned long t, u;
	int ret;

	ret = cmf_readall(to_ccwdev(dev), &data);
	if (ret == -EAGAIN || ret == -ENODEV)
		/* No data (yet/currently) available to use for calculation. */
		return sprintf(buf, "n/a\n");
	else if (ret)
		return ret;

	utilization = data.device_connect_time +
		      data.function_pending_time +
		      data.device_disconnect_time;

	/* shift to avoid long long division */
	while (-1ul < (data.elapsed_time | utilization)) {
		utilization >>= 8;
		data.elapsed_time >>= 8;
	}

	/* calculate value in 0.1 percent units */
	t = (unsigned long) data.elapsed_time / 1000;
	u = (unsigned long) utilization / t;

	return sprintf(buf, "%02ld.%01ld%%\n", u/ 10, u - (u/ 10) * 10);
}