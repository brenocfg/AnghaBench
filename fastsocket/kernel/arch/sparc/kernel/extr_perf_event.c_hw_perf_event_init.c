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
struct pmu {int dummy; } ;
struct perf_event {int dummy; } ;

/* Variables and functions */
 struct pmu const* ERR_PTR (int) ; 
 int __hw_perf_event_init (struct perf_event*) ; 
 struct pmu const pmu ; 

const struct pmu *hw_perf_event_init(struct perf_event *event)
{
	int err = __hw_perf_event_init(event);

	if (err)
		return ERR_PTR(err);
	return &pmu;
}