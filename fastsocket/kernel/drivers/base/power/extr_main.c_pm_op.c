#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct dev_pm_ops {int (* suspend ) (struct device*) ;int (* resume ) (struct device*) ;int (* freeze ) (struct device*) ;int (* poweroff ) (struct device*) ;int (* thaw ) (struct device*) ;int (* restore ) (struct device*) ;} ;
struct TYPE_3__ {int event; } ;
typedef  TYPE_1__ pm_message_t ;

/* Variables and functions */
 int EINVAL ; 
#define  PM_EVENT_FREEZE 135 
#define  PM_EVENT_HIBERNATE 134 
#define  PM_EVENT_QUIESCE 133 
#define  PM_EVENT_RECOVER 132 
#define  PM_EVENT_RESTORE 131 
#define  PM_EVENT_RESUME 130 
#define  PM_EVENT_SUSPEND 129 
#define  PM_EVENT_THAW 128 
 int stub1 (struct device*) ; 
 int stub2 (struct device*) ; 
 int stub3 (struct device*) ; 
 int stub4 (struct device*) ; 
 int stub5 (struct device*) ; 
 int stub6 (struct device*) ; 
 int /*<<< orphan*/  suspend_report_result (int (*) (struct device*),int) ; 

__attribute__((used)) static int pm_op(struct device *dev,
		 const struct dev_pm_ops *ops,
		 pm_message_t state)
{
	int error = 0;

	switch (state.event) {
#ifdef CONFIG_SUSPEND
	case PM_EVENT_SUSPEND:
		if (ops->suspend) {
			error = ops->suspend(dev);
			suspend_report_result(ops->suspend, error);
		}
		break;
	case PM_EVENT_RESUME:
		if (ops->resume) {
			error = ops->resume(dev);
			suspend_report_result(ops->resume, error);
		}
		break;
#endif /* CONFIG_SUSPEND */
#ifdef CONFIG_HIBERNATION
	case PM_EVENT_FREEZE:
	case PM_EVENT_QUIESCE:
		if (ops->freeze) {
			error = ops->freeze(dev);
			suspend_report_result(ops->freeze, error);
		}
		break;
	case PM_EVENT_HIBERNATE:
		if (ops->poweroff) {
			error = ops->poweroff(dev);
			suspend_report_result(ops->poweroff, error);
		}
		break;
	case PM_EVENT_THAW:
	case PM_EVENT_RECOVER:
		if (ops->thaw) {
			error = ops->thaw(dev);
			suspend_report_result(ops->thaw, error);
		}
		break;
	case PM_EVENT_RESTORE:
		if (ops->restore) {
			error = ops->restore(dev);
			suspend_report_result(ops->restore, error);
		}
		break;
#endif /* CONFIG_HIBERNATION */
	default:
		error = -EINVAL;
	}
	return error;
}