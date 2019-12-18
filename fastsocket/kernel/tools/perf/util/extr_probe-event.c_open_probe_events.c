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
 int ENOENT ; 
 int /*<<< orphan*/  O_APPEND ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_RDWR ; 
 int PATH_MAX ; 
 char* debugfs_find_mountpoint () ; 
 int e_snprintf (char*,int,char*,char const*,char const*) ; 
 int open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 int /*<<< orphan*/  print_warn_msg (char*,int) ; 
 int /*<<< orphan*/  probe_event_dry_run ; 

__attribute__((used)) static int open_probe_events(const char *trace_file, bool readwrite,
				bool is_kprobe)
{
	char buf[PATH_MAX];
	const char *__debugfs;
	int ret;

	__debugfs = debugfs_find_mountpoint();
	if (__debugfs == NULL) {
		pr_warning("Debugfs is not mounted.\n");
		return -ENOENT;
	}

	ret = e_snprintf(buf, PATH_MAX, "%s/%s", __debugfs, trace_file);
	if (ret >= 0) {
		pr_debug("Opening %s write=%d\n", buf, readwrite);
		if (readwrite && !probe_event_dry_run)
			ret = open(buf, O_RDWR, O_APPEND);
		else
			ret = open(buf, O_RDONLY, 0);

		if (ret < 0)
			print_warn_msg(buf, is_kprobe);
	}
	return ret;
}