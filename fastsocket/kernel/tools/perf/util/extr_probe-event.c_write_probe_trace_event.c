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
struct probe_trace_event {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe_event_dry_run ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* synthesize_probe_trace_command (struct probe_trace_event*) ; 
 int write (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_probe_trace_event(int fd, struct probe_trace_event *tev)
{
	int ret = 0;
	char *buf = synthesize_probe_trace_command(tev);

	if (!buf) {
		pr_debug("Failed to synthesize probe trace event.\n");
		return -EINVAL;
	}

	pr_debug("Writing event: %s\n", buf);
	if (!probe_event_dry_run) {
		ret = write(fd, buf, strlen(buf));
		if (ret <= 0)
			pr_warning("Failed to write event: %s\n",
				   strerror(errno));
	}
	free(buf);
	return ret;
}