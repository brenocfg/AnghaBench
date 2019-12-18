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
typedef  size_t u64 ;
struct perf_event_attr {int type; size_t config; int /*<<< orphan*/  exclude_user; int /*<<< orphan*/  exclude_kernel; int /*<<< orphan*/  exclude_hv; } ;
struct hw_perf_event {size_t config; int /*<<< orphan*/  config_base; } ;
struct perf_event {int /*<<< orphan*/  destroy; struct hw_perf_event hw; struct perf_event_attr attr; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (size_t*) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 size_t PERF_CPUM_CF_MAX_CTR ; 
#define  PERF_TYPE_HARDWARE 129 
#define  PERF_TYPE_RAW 128 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 size_t* cpumf_generic_events_basic ; 
 size_t* cpumf_generic_events_user ; 
 int /*<<< orphan*/  get_counter_set (size_t) ; 
 int /*<<< orphan*/  hw_perf_event_destroy ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  num_events ; 
 int /*<<< orphan*/  pmc_reserve_mutex ; 
 scalar_t__ reserve_pmc_hardware () ; 
 int validate_ctr_auth (struct hw_perf_event*) ; 
 int validate_ctr_version (struct hw_perf_event*) ; 
 int validate_event (struct hw_perf_event*) ; 

__attribute__((used)) static int __hw_perf_event_init(struct perf_event *event)
{
	struct perf_event_attr *attr = &event->attr;
	struct hw_perf_event *hwc = &event->hw;
	int err;
	u64 ev;

	switch (attr->type) {
	case PERF_TYPE_RAW:
		/* Raw events are used to access counters directly,
		 * hence do not permit excludes */
		if (attr->exclude_kernel || attr->exclude_user ||
		    attr->exclude_hv)
			return -EOPNOTSUPP;
		ev = attr->config;
		break;

	case PERF_TYPE_HARDWARE:
		ev = attr->config;
		/* Count user space (problem-state) only */
		if (!attr->exclude_user && attr->exclude_kernel) {
			if (ev >= ARRAY_SIZE(cpumf_generic_events_user))
				return -EOPNOTSUPP;
			ev = cpumf_generic_events_user[ev];

		/* No support for kernel space counters only */
		} else if (!attr->exclude_kernel && attr->exclude_user) {
			return -EOPNOTSUPP;

		/* Count user and kernel space */
		} else {
			if (ev >= ARRAY_SIZE(cpumf_generic_events_basic))
				return -EOPNOTSUPP;
			ev = cpumf_generic_events_basic[ev];
		}
		break;

	default:
		return -ENOENT;
	}

	if (ev == -1)
		return -ENOENT;

	if (ev >= PERF_CPUM_CF_MAX_CTR)
		return -EINVAL;

	/* Use the hardware perf event structure to store the counter number
	 * in 'config' member and the counter set to which the counter belongs
	 * in the 'config_base'.  The counter set (config_base) is then used
	 * to enable/disable the counters.
	 */
	hwc->config = ev;
	hwc->config_base = get_counter_set(ev);

	/* Validate the counter that is assigned to this event.
	 * Because the counter facility can use numerous counters at the
	 * same time without constraints, it is not necessary to explicity
	 * validate event groups (event->group_leader != event).
	 */
	err = validate_event(hwc);
	if (err)
		return err;

	/* Initialize for using the CPU-measurement counter facility */
	if (!atomic_inc_not_zero(&num_events)) {
		mutex_lock(&pmc_reserve_mutex);
		if (atomic_read(&num_events) == 0 && reserve_pmc_hardware())
			err = -EBUSY;
		else
			atomic_inc(&num_events);
		mutex_unlock(&pmc_reserve_mutex);
	}
	event->destroy = hw_perf_event_destroy;

	/* Finally, validate version and authorization of the counter set */
	err = validate_ctr_auth(hwc);
	if (!err)
		err = validate_ctr_version(hwc);

	return err;
}