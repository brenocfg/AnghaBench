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
typedef  int /*<<< orphan*/  kd_events ;
typedef  int /*<<< orphan*/  kd_event_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int KDEBUG_ENABLE_SERIAL ; 
 int KDEBUG_ENABLE_TRACE ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  KTRACE_KDEBUG ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  disable_wrap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int kd_early_done ; 
 int /*<<< orphan*/  kdbg_enable_typefilter () ; 
 scalar_t__ kdbg_initialize_typefilter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kdbg_lock_init () ; 
 scalar_t__ kdbg_reinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdbg_set_nkdbufs (unsigned int) ; 
 int /*<<< orphan*/  kdbg_set_tracing_enabled (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kdbg_set_typefilter_string (char const*) ; 
 int /*<<< orphan*/  kdbg_thrmap_init () ; 
 scalar_t__ kdebug_serial ; 
 int /*<<< orphan*/  kernel_debug_early_end () ; 
 int /*<<< orphan*/  kernel_debug_string_early (char*) ; 
 int /*<<< orphan*/  ktrace_end_single_threaded () ; 
 int /*<<< orphan*/  ktrace_kernel_configure (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktrace_start_single_threaded () ; 
 scalar_t__ ml_set_interrupts_enabled (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
kdebug_trace_start(unsigned int n_events, const char *filter_desc,
	boolean_t wrapping, boolean_t at_wake)
{
	if (!n_events) {
		kd_early_done = true;
		return;
	}

	ktrace_start_single_threaded();

	kdbg_lock_init();

	ktrace_kernel_configure(KTRACE_KDEBUG);

	kdbg_set_nkdbufs(n_events);

	kernel_debug_string_early("start_kern_tracing");

	if (kdbg_reinit(TRUE)) {
		printf("error from kdbg_reinit, kernel tracing not started\n");
		goto out;
	}

	/*
	 * Wrapping is disabled because boot and wake tracing is interested in
	 * the earliest events, at the expense of later ones.
	 */
	if (!wrapping) {
		uint32_t old1, old2;
		(void)disable_wrap(&old1, &old2);
	}

	if (filter_desc && filter_desc[0] != '\0') {
		if (kdbg_initialize_typefilter(NULL) == KERN_SUCCESS) {
			kdbg_set_typefilter_string(filter_desc);
			kdbg_enable_typefilter();
		}
	}

	/*
	 * Hold off interrupts between getting a thread map and enabling trace
	 * and until the early traces are recorded.
	 */
	boolean_t s = ml_set_interrupts_enabled(FALSE);

	if (at_wake) {
		kdbg_thrmap_init();
	}

	kdbg_set_tracing_enabled(TRUE, KDEBUG_ENABLE_TRACE | (kdebug_serial ?
	                         KDEBUG_ENABLE_SERIAL : 0));

	if (!at_wake) {
		/*
		 * Transfer all very early events from the static buffer into the real
		 * buffers.
		 */
		kernel_debug_early_end();
	}

	ml_set_interrupts_enabled(s);

	printf("kernel tracing started with %u events\n", n_events);

#if KDEBUG_MOJO_TRACE
	if (kdebug_serial) {
		printf("serial output enabled with %lu named events\n",
		sizeof(kd_events)/sizeof(kd_event_t));
	}
#endif /* KDEBUG_MOJO_TRACE */

out:
	ktrace_end_single_threaded();
}