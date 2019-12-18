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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int EBUSY ; 
 int HOST_REBOOT_HALT ; 
 int HOST_REBOOT_UPSDELAY ; 
 int /*<<< orphan*/  IOSystemShutdownNotification (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSCompareAndSwap (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int RB_HALT ; 
 int RB_NOSYNC ; 
 int RB_PANIC ; 
 int RB_POWERDOWN ; 
 int RB_QUICK ; 
 int RB_UPSDELAY ; 
 int /*<<< orphan*/  audit_shutdown () ; 
 int count_busy_buffers () ; 
 int /*<<< orphan*/  delay_for_interval (int,int) ; 
 int /*<<< orphan*/  halt_log_enter (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  host_priv_self () ; 
 int /*<<< orphan*/  host_reboot (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_down_all () ; 
 int /*<<< orphan*/  kIOSystemShutdownNotificationStageProcessExit ; 
 int /*<<< orphan*/  kIOSystemShutdownNotificationStageRootUnmount ; 
 int /*<<< orphan*/  kdbg_dump_trace_to_file (char*) ; 
 scalar_t__ kdebug_enable ; 
 int /*<<< orphan*/  kdp_has_polled_corefile () ; 
 scalar_t__ mach_absolute_time () ; 
 int /*<<< orphan*/  panic_kernel (int,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  proc_shutdown () ; 
 int /*<<< orphan*/  sync (int /*<<< orphan*/ ,void*,int*) ; 
 int /*<<< orphan*/  system_inshutdown ; 
 int /*<<< orphan*/  unmountroot_pre_hook () ; 
 int /*<<< orphan*/  vfs_unmountall () ; 

int
reboot_kernel(int howto, char *message)
{
	int hostboot_option=0;
	uint64_t startTime;

	if ((howto & (RB_PANIC | RB_QUICK)) == (RB_PANIC | RB_QUICK)) {
		panic_kernel(howto, message);
	}

	if (!OSCompareAndSwap(0, 1, &system_inshutdown)) {
		if ( (howto&RB_QUICK) == RB_QUICK)
			goto force_reboot;
		return (EBUSY);
	}
	/*
	 * Notify the power management root domain that the system will shut down.
	 */
	IOSystemShutdownNotification(kIOSystemShutdownNotificationStageProcessExit);

	if ((howto&RB_QUICK)==RB_QUICK) {
		printf("Quick reboot...\n");
		if ((howto&RB_NOSYNC)==0) {
			sync((proc_t)NULL, (void *)NULL, (int *)NULL);
		}
	}
	else if ((howto&RB_NOSYNC)==0) {
		int iter, nbusy;

		printf("syncing disks... ");

		/*
		 * Release vnodes held by texts before sync.
		 */

		/* handle live procs (deallocate their root and current directories), suspend initproc */

		startTime = mach_absolute_time();
		proc_shutdown();
		halt_log_enter("proc_shutdown", 0, mach_absolute_time() - startTime);

#if CONFIG_AUDIT
		startTime = mach_absolute_time();
		audit_shutdown();
		halt_log_enter("audit_shutdown", 0, mach_absolute_time() - startTime);
#endif

		if (unmountroot_pre_hook != NULL)
			unmountroot_pre_hook();

		startTime = mach_absolute_time();
		sync((proc_t)NULL, (void *)NULL, (int *)NULL);

		if (kdebug_enable) {
			startTime = mach_absolute_time();
			kdbg_dump_trace_to_file("/var/log/shutdown/shutdown.trace");
			halt_log_enter("shutdown.trace", 0, mach_absolute_time() - startTime);
		}

		IOSystemShutdownNotification(kIOSystemShutdownNotificationStageRootUnmount);

		/*
		 * Unmount filesystems
		 */

#if DEVELOPMENT || DEBUG
		if (!(howto & RB_PANIC) || !kdp_has_polled_corefile())
#endif /* DEVELOPMENT || DEBUG */
		{
			startTime = mach_absolute_time();
			vfs_unmountall();
			halt_log_enter("vfs_unmountall", 0, mach_absolute_time() - startTime);
		}

		/* Wait for the buffer cache to clean remaining dirty buffers */
		startTime = mach_absolute_time();
		for (iter = 0; iter < 100; iter++) {
			nbusy = count_busy_buffers();
			if (nbusy == 0)
				break;
			printf("%d ", nbusy);
			delay_for_interval( 1 * nbusy, 1000 * 1000);
		}
		if (nbusy)
			printf("giving up\n");
		else
			printf("done\n");
		halt_log_enter("bufferclean", 0, mach_absolute_time() - startTime);
	}
#if NETWORKING
	/*
	 * Can't just use an splnet() here to disable the network
	 * because that will lock out softints which the disk
	 * drivers depend on to finish DMAs.
	 */
	startTime = mach_absolute_time();
	if_down_all();
	halt_log_enter("if_down_all", 0, mach_absolute_time() - startTime);
#endif /* NETWORKING */

force_reboot:

	if (howto & RB_PANIC) {
		panic_kernel(howto, message);
	}

	if (howto & RB_POWERDOWN)
		hostboot_option = HOST_REBOOT_HALT;
	if (howto & RB_HALT)
		hostboot_option = HOST_REBOOT_HALT;

	if (howto & RB_UPSDELAY) {
		hostboot_option = HOST_REBOOT_UPSDELAY;
	}

	host_reboot(host_priv_self(), hostboot_option);
	/*
	 * should not be reached
	 */
	return (0);
}