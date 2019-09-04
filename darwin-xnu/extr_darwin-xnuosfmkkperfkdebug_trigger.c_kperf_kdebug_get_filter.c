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
typedef  int /*<<< orphan*/  uint32_t ;
struct kperf_kdebug_filter {int /*<<< orphan*/  n_debugids; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int kperf_init () ; 
 struct kperf_kdebug_filter* kperf_kdebug_filter ; 

uint32_t
kperf_kdebug_get_filter(struct kperf_kdebug_filter **filter)
{
	int err;

	if ((err = kperf_init())) {
		return 0;
	}

	assert(filter != NULL);

	*filter = kperf_kdebug_filter;
	return kperf_kdebug_filter->n_debugids;
}