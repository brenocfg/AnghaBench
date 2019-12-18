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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cardstate {int waiting; int /*<<< orphan*/  mutex; int /*<<< orphan*/  waitqueue; int /*<<< orphan*/  at_state; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_CMD ; 
 size_t EINVAL ; 
 size_t ENOMEM ; 
 size_t ERESTARTSYS ; 
 int /*<<< orphan*/  EV_PROC_CIDMODE ; 
 struct cardstate* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gigaset_add_event (struct cardstate*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gigaset_schedule_event (struct cardstate*) ; 
 int /*<<< orphan*/  isspace (int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 long simple_strtol (char const*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t set_cidmode(struct device *dev, struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct cardstate *cs = dev_get_drvdata(dev);
	long int value;
	char *end;

	value = simple_strtol(buf, &end, 0);
	while (*end)
		if (!isspace(*end++))
			return -EINVAL;
	if (value < 0 || value > 1)
			return -EINVAL;

	if (mutex_lock_interruptible(&cs->mutex))
		return -ERESTARTSYS; // FIXME -EINTR?

	cs->waiting = 1;
	if (!gigaset_add_event(cs, &cs->at_state, EV_PROC_CIDMODE,
			       NULL, value, NULL)) {
		cs->waiting = 0;
		mutex_unlock(&cs->mutex);
		return -ENOMEM;
	}

	gig_dbg(DEBUG_CMD, "scheduling PROC_CIDMODE");
	gigaset_schedule_event(cs);

	wait_event(cs->waitqueue, !cs->waiting);

	mutex_unlock(&cs->mutex);

	return count;
}