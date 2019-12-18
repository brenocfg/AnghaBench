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
struct TYPE_2__ {scalar_t__ n_debugids; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int kperf_init () ; 
 scalar_t__ kperf_kdebug_action ; 
 int /*<<< orphan*/  kperf_kdebug_active ; 
 TYPE_1__* kperf_kdebug_filter ; 

__attribute__((used)) static void
kperf_kdebug_update(void)
{
	int err;

	if ((err = kperf_init())) {
		return;
	}

	if (kperf_kdebug_action != 0 &&
	    kperf_kdebug_filter->n_debugids != 0)
	{
		kperf_kdebug_active = TRUE;
	} else {
		kperf_kdebug_active = FALSE;
	}
}