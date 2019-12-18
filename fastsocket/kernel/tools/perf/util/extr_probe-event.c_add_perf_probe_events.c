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
struct perf_probe_event {int /*<<< orphan*/  uprobes; } ;
struct __event_package {int ntevs; struct __event_package* tevs; struct perf_probe_event* pev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int __add_probe_trace_events (struct perf_probe_event*,struct __event_package*,int,int) ; 
 int /*<<< orphan*/  clear_probe_trace_event (struct __event_package*) ; 
 int convert_to_probe_trace_events (struct perf_probe_event*,struct __event_package**,int,char const*) ; 
 int /*<<< orphan*/  free (struct __event_package*) ; 
 int init_user_exec () ; 
 int init_vmlinux () ; 
 struct __event_package* zalloc (int) ; 

int add_perf_probe_events(struct perf_probe_event *pevs, int npevs,
			  int max_tevs, const char *target, bool force_add)
{
	int i, j, ret;
	struct __event_package *pkgs;

	ret = 0;
	pkgs = zalloc(sizeof(struct __event_package) * npevs);

	if (pkgs == NULL)
		return -ENOMEM;

	if (!pevs->uprobes)
		/* Init vmlinux path */
		ret = init_vmlinux();
	else
		ret = init_user_exec();

	if (ret < 0) {
		free(pkgs);
		return ret;
	}

	/* Loop 1: convert all events */
	for (i = 0; i < npevs; i++) {
		pkgs[i].pev = &pevs[i];
		/* Convert with or without debuginfo */
		ret  = convert_to_probe_trace_events(pkgs[i].pev,
						     &pkgs[i].tevs,
						     max_tevs,
						     target);
		if (ret < 0)
			goto end;
		pkgs[i].ntevs = ret;
	}

	/* Loop 2: add all events */
	for (i = 0; i < npevs; i++) {
		ret = __add_probe_trace_events(pkgs[i].pev, pkgs[i].tevs,
						pkgs[i].ntevs, force_add);
		if (ret < 0)
			break;
	}
end:
	/* Loop 3: cleanup and free trace events  */
	for (i = 0; i < npevs; i++) {
		for (j = 0; j < pkgs[i].ntevs; j++)
			clear_probe_trace_event(&pkgs[i].tevs[j]);
		free(pkgs[i].tevs);
	}
	free(pkgs);

	return ret;
}