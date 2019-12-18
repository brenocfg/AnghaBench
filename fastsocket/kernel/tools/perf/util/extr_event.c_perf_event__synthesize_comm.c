#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int size; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int pid; int tid; TYPE_1__ header; struct TYPE_6__* comm; } ;
union perf_event {TYPE_2__ comm; } ;
typedef  int /*<<< orphan*/  u64 ;
struct perf_tool {int dummy; } ;
struct machine {int id_hdr_size; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int pid_t ;
typedef  scalar_t__ (* perf_event__handler_t ) (struct perf_tool*,union perf_event*,int /*<<< orphan*/ *,struct machine*) ;
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int PATH_MAX ; 
 size_t PERF_ALIGN (size_t,int) ; 
 int /*<<< orphan*/  PERF_RECORD_COMM ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int perf_event__get_comm_tgid (int,TYPE_2__*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 
 int /*<<< orphan*/  readdir_r (int /*<<< orphan*/ *,struct dirent*,struct dirent**) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int strlen (TYPE_2__*) ; 
 int strtol (int /*<<< orphan*/ ,char**,int) ; 
 int /*<<< orphan*/  synth_sample ; 

__attribute__((used)) static pid_t perf_event__synthesize_comm(struct perf_tool *tool,
					 union perf_event *event, pid_t pid,
					 int full,
					 perf_event__handler_t process,
					 struct machine *machine)
{
	char filename[PATH_MAX];
	size_t size;
	DIR *tasks;
	struct dirent dirent, *next;
	pid_t tgid;

	memset(&event->comm, 0, sizeof(event->comm));

	tgid = perf_event__get_comm_tgid(pid, event->comm.comm,
					 sizeof(event->comm.comm));
	if (tgid < 0)
		goto out;

	event->comm.pid = tgid;
	event->comm.header.type = PERF_RECORD_COMM;

	size = strlen(event->comm.comm) + 1;
	size = PERF_ALIGN(size, sizeof(u64));
	memset(event->comm.comm + size, 0, machine->id_hdr_size);
	event->comm.header.size = (sizeof(event->comm) -
				(sizeof(event->comm.comm) - size) +
				machine->id_hdr_size);
	if (!full) {
		event->comm.tid = pid;

		if (process(tool, event, &synth_sample, machine) != 0)
			return -1;

		goto out;
	}

	snprintf(filename, sizeof(filename), "/proc/%d/task", pid);

	tasks = opendir(filename);
	if (tasks == NULL) {
		pr_debug("couldn't open %s\n", filename);
		return 0;
	}

	while (!readdir_r(tasks, &dirent, &next) && next) {
		char *end;
		pid = strtol(dirent.d_name, &end, 10);
		if (*end)
			continue;

		/* already have tgid; jut want to update the comm */
		(void) perf_event__get_comm_tgid(pid, event->comm.comm,
					 sizeof(event->comm.comm));

		size = strlen(event->comm.comm) + 1;
		size = PERF_ALIGN(size, sizeof(u64));
		memset(event->comm.comm + size, 0, machine->id_hdr_size);
		event->comm.header.size = (sizeof(event->comm) -
					  (sizeof(event->comm.comm) - size) +
					  machine->id_hdr_size);

		event->comm.tid = pid;

		if (process(tool, event, &synth_sample, machine) != 0) {
			tgid = -1;
			break;
		}
	}

	closedir(tasks);
out:
	return tgid;
}