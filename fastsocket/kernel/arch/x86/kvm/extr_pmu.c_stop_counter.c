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
struct kvm_pmc {int /*<<< orphan*/ * perf_event; int /*<<< orphan*/  counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_event_release_kernel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_pmc (struct kvm_pmc*) ; 

__attribute__((used)) static void stop_counter(struct kvm_pmc *pmc)
{
	if (pmc->perf_event) {
		pmc->counter = read_pmc(pmc);
		perf_event_release_kernel(pmc->perf_event);
		pmc->perf_event = NULL;
	}
}