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
typedef  void* u64 ;
typedef  void* u32 ;
struct work_atoms {int dummy; } ;
struct thread {int dummy; } ;
struct perf_sched {int /*<<< orphan*/  cmp_pid; int /*<<< orphan*/  atom_root; } ;
struct perf_sample {int cpu; void* time; } ;
struct perf_evsel {int dummy; } ;
struct machine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int MAX_CPUS ; 
 int /*<<< orphan*/  add_runtime_event (struct work_atoms*,void* const,void*) ; 
 scalar_t__ add_sched_out_event (struct work_atoms*,char,void*) ; 
 struct thread* machine__findnew_thread (struct machine*,void* const) ; 
 void* perf_evsel__intval (struct perf_evsel*,struct perf_sample*,char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ thread_atoms_insert (struct perf_sched*,struct thread*) ; 
 struct work_atoms* thread_atoms_search (int /*<<< orphan*/ *,struct thread*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int latency_runtime_event(struct perf_sched *sched,
				 struct perf_evsel *evsel,
				 struct perf_sample *sample,
				 struct machine *machine)
{
	const u32 pid	   = perf_evsel__intval(evsel, sample, "pid");
	const u64 runtime  = perf_evsel__intval(evsel, sample, "runtime");
	struct thread *thread = machine__findnew_thread(machine, pid);
	struct work_atoms *atoms = thread_atoms_search(&sched->atom_root, thread, &sched->cmp_pid);
	u64 timestamp = sample->time;
	int cpu = sample->cpu;

	BUG_ON(cpu >= MAX_CPUS || cpu < 0);
	if (!atoms) {
		if (thread_atoms_insert(sched, thread))
			return -1;
		atoms = thread_atoms_search(&sched->atom_root, thread, &sched->cmp_pid);
		if (!atoms) {
			pr_err("in-event: Internal tree error");
			return -1;
		}
		if (add_sched_out_event(atoms, 'R', timestamp))
			return -1;
	}

	add_runtime_event(atoms, runtime, timestamp);
	return 0;
}