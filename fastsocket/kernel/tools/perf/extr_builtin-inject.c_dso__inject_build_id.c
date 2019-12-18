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
struct perf_tool {int dummy; } ;
struct machine {int dummy; } ;
struct dso {int /*<<< orphan*/  long_name; scalar_t__ kernel; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_RECORD_MISC_KERNEL ; 
 int /*<<< orphan*/  PERF_RECORD_MISC_USER ; 
 scalar_t__ dso__read_build_id (struct dso*) ; 
 int /*<<< orphan*/  perf_event__repipe ; 
 int perf_event__synthesize_build_id (struct perf_tool*,struct dso*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct machine*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dso__inject_build_id(struct dso *self, struct perf_tool *tool,
				struct machine *machine)
{
	u16 misc = PERF_RECORD_MISC_USER;
	int err;

	if (dso__read_build_id(self) < 0) {
		pr_debug("no build_id found for %s\n", self->long_name);
		return -1;
	}

	if (self->kernel)
		misc = PERF_RECORD_MISC_KERNEL;

	err = perf_event__synthesize_build_id(tool, self, misc, perf_event__repipe,
					      machine);
	if (err) {
		pr_err("Can't synthesize build_id event for %s\n", self->long_name);
		return -1;
	}

	return 0;
}