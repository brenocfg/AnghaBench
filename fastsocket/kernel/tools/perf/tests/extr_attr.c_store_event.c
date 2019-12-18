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
struct perf_event_attr {int type; int /*<<< orphan*/  config; } ;
typedef  unsigned long pid_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int PATH_MAX ; 
 char* PRIu32 ; 
 int /*<<< orphan*/  WRITE_ASS (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  __WRITE_ASS (unsigned long,char*,unsigned long) ; 
 int /*<<< orphan*/  bp_type ; 
 int /*<<< orphan*/  branch_sample_type ; 
 int /*<<< orphan*/  comm ; 
 int /*<<< orphan*/  config ; 
 int /*<<< orphan*/  config1 ; 
 int /*<<< orphan*/  config2 ; 
 char* dir ; 
 int /*<<< orphan*/  disabled ; 
 int /*<<< orphan*/  enable_on_exec ; 
 int /*<<< orphan*/  exclude_guest ; 
 int /*<<< orphan*/  exclude_host ; 
 int /*<<< orphan*/  exclude_hv ; 
 int /*<<< orphan*/  exclude_idle ; 
 int /*<<< orphan*/  exclude_kernel ; 
 int /*<<< orphan*/  exclude_user ; 
 int /*<<< orphan*/  exclusive ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  freq ; 
 int /*<<< orphan*/  inherit ; 
 int /*<<< orphan*/  inherit_stat ; 
 int /*<<< orphan*/  mmap ; 
 int /*<<< orphan*/  mmap_data ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pinned ; 
 int /*<<< orphan*/  precise_ip ; 
 int /*<<< orphan*/  read_format ; 
 int /*<<< orphan*/  sample_id_all ; 
 int /*<<< orphan*/  sample_period ; 
 int /*<<< orphan*/  sample_type ; 
 int /*<<< orphan*/  size ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  task ; 
 int /*<<< orphan*/  type ; 
 int /*<<< orphan*/  wakeup_events ; 
 int /*<<< orphan*/  watermark ; 

__attribute__((used)) static int store_event(struct perf_event_attr *attr, pid_t pid, int cpu,
		       int fd, int group_fd, unsigned long flags)
{
	FILE *file;
	char path[PATH_MAX];

	snprintf(path, PATH_MAX, "%s/event-%d-%llu-%d", dir,
		 attr->type, attr->config, fd);

	file = fopen(path, "w+");
	if (!file) {
		perror("test attr - failed to open event file");
		return -1;
	}

	if (fprintf(file, "[event-%d-%llu-%d]\n",
		    attr->type, attr->config, fd) < 0) {
		perror("test attr - failed to write event file");
		fclose(file);
		return -1;
	}

	/* syscall arguments */
	__WRITE_ASS(fd,       "d", fd);
	__WRITE_ASS(group_fd, "d", group_fd);
	__WRITE_ASS(cpu,      "d", cpu);
	__WRITE_ASS(pid,      "d", pid);
	__WRITE_ASS(flags,   "lu", flags);

	/* struct perf_event_attr */
	WRITE_ASS(type,   PRIu32);
	WRITE_ASS(size,   PRIu32);
	WRITE_ASS(config,  "llu");
	WRITE_ASS(sample_period, "llu");
	WRITE_ASS(sample_type,   "llu");
	WRITE_ASS(read_format,   "llu");
	WRITE_ASS(disabled,       "d");
	WRITE_ASS(inherit,        "d");
	WRITE_ASS(pinned,         "d");
	WRITE_ASS(exclusive,      "d");
	WRITE_ASS(exclude_user,   "d");
	WRITE_ASS(exclude_kernel, "d");
	WRITE_ASS(exclude_hv,     "d");
	WRITE_ASS(exclude_idle,   "d");
	WRITE_ASS(mmap,           "d");
	WRITE_ASS(comm,           "d");
	WRITE_ASS(freq,           "d");
	WRITE_ASS(inherit_stat,   "d");
	WRITE_ASS(enable_on_exec, "d");
	WRITE_ASS(task,           "d");
	WRITE_ASS(watermark,      "d");
	WRITE_ASS(precise_ip,     "d");
	WRITE_ASS(mmap_data,      "d");
	WRITE_ASS(sample_id_all,  "d");
	WRITE_ASS(exclude_host,   "d");
	WRITE_ASS(exclude_guest,  "d");
/*
 * RHEL6 - no support for:
 *   exclude_callchain_kernel
 *   exclude_callchain_user
 *   sample_regs_user
 *   sample_stack_user
 *
	WRITE_ASS(exclude_callchain_kernel, "d");
	WRITE_ASS(exclude_callchain_user, "d");
*/
	WRITE_ASS(wakeup_events, PRIu32);
	WRITE_ASS(bp_type, PRIu32);
	WRITE_ASS(config1, "llu");
	WRITE_ASS(config2, "llu");
	WRITE_ASS(branch_sample_type, "llu");
/*
	WRITE_ASS(sample_regs_user,   "llu");
	WRITE_ASS(sample_stack_user,  PRIu32);
*/

	fclose(file);
	return 0;
}