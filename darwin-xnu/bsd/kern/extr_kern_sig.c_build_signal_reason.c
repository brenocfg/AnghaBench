#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  TYPE_1__* proc_t ;
typedef  TYPE_2__* os_reason_t ;
typedef  int /*<<< orphan*/  mach_vm_address_t ;
struct TYPE_9__ {int /*<<< orphan*/  osr_kcd_descriptor; } ;
struct TYPE_8__ {char const* p_pid; char const* p_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  KCDATA_TYPE_PID ; 
 int /*<<< orphan*/  KCDATA_TYPE_PROCNAME ; 
 scalar_t__ KERN_SUCCESS ; 
 TYPE_2__* OS_REASON_NULL ; 
 int /*<<< orphan*/  OS_REASON_SIGNAL ; 
 TYPE_1__* current_proc () ; 
 int kcdata_estimate_required_buffer_size (int,int) ; 
 scalar_t__ kcdata_get_memory_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kcdata_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int os_reason_alloc_buffer_noblock (TYPE_2__*,int) ; 
 TYPE_2__* os_reason_create (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static os_reason_t
build_signal_reason(int signum, const char *procname)
{
	os_reason_t signal_reason = OS_REASON_NULL;
	proc_t sender_proc = current_proc();
	uint32_t reason_buffer_size_estimate = 0, proc_name_length = 0;
	const char *default_sender_procname = "unknown";
	mach_vm_address_t data_addr;
	int ret;

	signal_reason = os_reason_create(OS_REASON_SIGNAL, signum);
	if (signal_reason == OS_REASON_NULL) {
		printf("build_signal_reason: unable to allocate signal reason structure.\n");
		return signal_reason;
	}

	reason_buffer_size_estimate = kcdata_estimate_required_buffer_size(2, sizeof(sender_proc->p_name) +
										sizeof(sender_proc->p_pid));

	ret = os_reason_alloc_buffer_noblock(signal_reason, reason_buffer_size_estimate);
	if (ret != 0) {
		printf("build_signal_reason: unable to allocate signal reason buffer.\n");
		return signal_reason;
	}

	if (KERN_SUCCESS == kcdata_get_memory_addr(&signal_reason->osr_kcd_descriptor, KCDATA_TYPE_PID,
							sizeof(sender_proc->p_pid), &data_addr)) {
		kcdata_memcpy(&signal_reason->osr_kcd_descriptor, data_addr, &sender_proc->p_pid,
					sizeof(sender_proc->p_pid));
	} else {
		printf("build_signal_reason: exceeded space in signal reason buf, unable to log PID\n");
	}

	proc_name_length = sizeof(sender_proc->p_name);
	if (KERN_SUCCESS == kcdata_get_memory_addr(&signal_reason->osr_kcd_descriptor, KCDATA_TYPE_PROCNAME,
							proc_name_length, &data_addr)) {
		if (procname) {
			char truncated_procname[proc_name_length];
			strncpy((char *) &truncated_procname, procname, proc_name_length);
			truncated_procname[proc_name_length - 1] = '\0';

			kcdata_memcpy(&signal_reason->osr_kcd_descriptor, data_addr, truncated_procname,
					strlen((char *) &truncated_procname));
		} else if (*sender_proc->p_name) {
			kcdata_memcpy(&signal_reason->osr_kcd_descriptor, data_addr, &sender_proc->p_name,
					sizeof(sender_proc->p_name));
		} else {
			kcdata_memcpy(&signal_reason->osr_kcd_descriptor, data_addr, &default_sender_procname,
					strlen(default_sender_procname) + 1);
		}
	} else {
		printf("build_signal_reason: exceeded space in signal reason buf, unable to log procname\n");
	}

	return signal_reason;
}