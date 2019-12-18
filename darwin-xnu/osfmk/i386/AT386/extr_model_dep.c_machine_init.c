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

/* Variables and functions */
 int /*<<< orphan*/  clock_config () ; 
 int /*<<< orphan*/  cpu_data_realloc () ; 
 int /*<<< orphan*/  cpuid_cpu_display (char*) ; 
 int /*<<< orphan*/  cpuid_extfeature_display (char*) ; 
 int /*<<< orphan*/  cpuid_feature_display (char*) ; 
 int /*<<< orphan*/  debug_log_init () ; 
 int /*<<< orphan*/  efi_init () ; 
 int /*<<< orphan*/  init_fpu () ; 
 int /*<<< orphan*/  mtrr_init () ; 
 int /*<<< orphan*/  pat_init () ; 
 int /*<<< orphan*/  pmap_lowmem_finalize () ; 
 int /*<<< orphan*/  smp_init () ; 

void
machine_init(void)
{
	/* Now with VM up, switch to dynamically allocated cpu data */
	cpu_data_realloc();

        /* Ensure panic buffer is initialized. */
        debug_log_init();

	/*
	 * Display CPU identification
	 */
	cpuid_cpu_display("CPU identification");
	cpuid_feature_display("CPU features");
	cpuid_extfeature_display("CPU extended features");

        /*
         * Initialize EFI runtime services.
         */
        efi_init();

	smp_init();

	/*
	 * Set up to use floating point.
	 */
	init_fpu();

	/*
	 * Configure clock devices.
	 */
	clock_config();

#if CONFIG_MTRR
	/*
	 * Initialize MTRR from boot processor.
	 */
	mtrr_init();

	/*
	 * Set up PAT for boot processor.
	 */
	pat_init();
#endif

	/*
	 * Free lowmem pages and complete other setup
	 */
	pmap_lowmem_finalize();
}