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
typedef  int /*<<< orphan*/  u16 ;
struct machine {int /*<<< orphan*/  pid; int /*<<< orphan*/  user_dsos; int /*<<< orphan*/  kernel_dsos; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_RECORD_MISC_GUEST_KERNEL ; 
 int /*<<< orphan*/  PERF_RECORD_MISC_GUEST_USER ; 
 int /*<<< orphan*/  PERF_RECORD_MISC_KERNEL ; 
 int /*<<< orphan*/  PERF_RECORD_MISC_USER ; 
 int __dsos__write_buildid_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  machine__is_host (struct machine*) ; 

__attribute__((used)) static int machine__write_buildid_table(struct machine *machine, int fd)
{
	int err;
	u16 kmisc = PERF_RECORD_MISC_KERNEL,
	    umisc = PERF_RECORD_MISC_USER;

	if (!machine__is_host(machine)) {
		kmisc = PERF_RECORD_MISC_GUEST_KERNEL;
		umisc = PERF_RECORD_MISC_GUEST_USER;
	}

	err = __dsos__write_buildid_table(&machine->kernel_dsos, machine->pid,
					  kmisc, fd);
	if (err == 0)
		err = __dsos__write_buildid_table(&machine->user_dsos,
						  machine->pid, umisc, fd);
	return err;
}