#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device {TYPE_1__* bus; } ;
typedef  int /*<<< orphan*/  pm_message_t ;
struct TYPE_2__ {scalar_t__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_DEVICE (struct device*) ; 
 int /*<<< orphan*/  TRACE_RESUME (int) ; 
 int /*<<< orphan*/  pm_dev_dbg (struct device*,int /*<<< orphan*/ ,char*) ; 
 int pm_noirq_op (struct device*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int device_resume_noirq(struct device *dev, pm_message_t state)
{
	int error = 0;

	TRACE_DEVICE(dev);
	TRACE_RESUME(0);

	if (!dev->bus)
		goto End;

	if (dev->bus->pm) {
		pm_dev_dbg(dev, state, "EARLY ");
		error = pm_noirq_op(dev, dev->bus->pm, state);
	}
 End:
	TRACE_RESUME(error);
	return error;
}