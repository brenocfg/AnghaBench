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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ kdebug_serial ; 
 int /*<<< orphan*/  kdebug_trace_start (unsigned int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ log_leaks ; 

void
kdebug_init(unsigned int n_events, char *filter_desc, boolean_t wrapping)
{
	assert(filter_desc != NULL);

#if defined(__x86_64__)
	/* only trace MACH events when outputting kdebug to serial */
	if (kdebug_serial) {
		n_events = 1;
		if (filter_desc[0] == '\0') {
			filter_desc[0] = 'C';
			filter_desc[1] = '1';
			filter_desc[2] = '\0';
		}
	}
#endif /* defined(__x86_64__) */

	if (log_leaks && n_events == 0) {
		n_events = 200000;
	}

	kdebug_trace_start(n_events, filter_desc, wrapping, FALSE);
}