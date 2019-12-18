#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ nsec; scalar_t__ sec; } ;
struct TYPE_4__ {int /*<<< orphan*/  nsec; int /*<<< orphan*/  sec; } ;
struct TYPE_6__ {scalar_t__ index; TYPE_2__ period; TYPE_1__ start; } ;
struct ptp_clock_request {TYPE_3__ perout; int /*<<< orphan*/  type; } ;
struct ptp_clock_info {scalar_t__ n_per_out; int (* enable ) (struct ptp_clock_info*,struct ptp_clock_request*,int) ;} ;
struct ptp_clock {struct ptp_clock_info* info; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PTP_CLK_REQ_PEROUT ; 
 struct ptp_clock* dev_get_drvdata (struct device*) ; 
 int sscanf (char const*,char*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int stub1 (struct ptp_clock_info*,struct ptp_clock_request*,int) ; 

__attribute__((used)) static ssize_t period_store(struct device *dev,
			    struct device_attribute *attr,
			    const char *buf, size_t count)
{
	struct ptp_clock *ptp = dev_get_drvdata(dev);
	struct ptp_clock_info *ops = ptp->info;
	struct ptp_clock_request req = { .type = PTP_CLK_REQ_PEROUT };
	int cnt, enable, err = -EINVAL;

	cnt = sscanf(buf, "%u %lld %u %lld %u", &req.perout.index,
		     &req.perout.start.sec, &req.perout.start.nsec,
		     &req.perout.period.sec, &req.perout.period.nsec);
	if (cnt != 5)
		goto out;
	if (req.perout.index >= ops->n_per_out)
		goto out;

	enable = req.perout.period.sec || req.perout.period.nsec;
	err = ops->enable(ops, &req, enable);
	if (err)
		goto out;

	return count;
out:
	return err;
}