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
struct pevent {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  bigendian () ; 
 int calc_data_size ; 
 int /*<<< orphan*/  die (char*) ; 
 char file_bigendian ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  host_bigendian ; 
 int input_fd ; 
 char long_size ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  page_size ; 
 int /*<<< orphan*/  pevent_print_funcs (struct pevent*) ; 
 int /*<<< orphan*/  pevent_print_printk (struct pevent*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  read4 (struct pevent*) ; 
 int /*<<< orphan*/  read_event_files (struct pevent*) ; 
 int /*<<< orphan*/  read_ftrace_files (struct pevent*) ; 
 int /*<<< orphan*/  read_ftrace_printk (struct pevent*) ; 
 int /*<<< orphan*/  read_header_files (struct pevent*) ; 
 int /*<<< orphan*/  read_or_die (char*,int) ; 
 int /*<<< orphan*/  read_proc_kallsyms (struct pevent*) ; 
 char* read_string () ; 
 struct pevent* read_trace_init (char,int /*<<< orphan*/ ) ; 
 int repipe ; 

ssize_t trace_report(int fd, struct pevent **ppevent, bool __repipe)
{
	char buf[BUFSIZ];
	char test[] = { 23, 8, 68 };
	char *version;
	int show_version = 0;
	int show_funcs = 0;
	int show_printk = 0;
	ssize_t size;

	calc_data_size = 1;
	repipe = __repipe;

	input_fd = fd;

	read_or_die(buf, 3);
	if (memcmp(buf, test, 3) != 0)
		die("no trace data in the file");

	read_or_die(buf, 7);
	if (memcmp(buf, "tracing", 7) != 0)
		die("not a trace file (missing 'tracing' tag)");

	version = read_string();
	if (show_version)
		printf("version = %s\n", version);
	free(version);

	read_or_die(buf, 1);
	file_bigendian = buf[0];
	host_bigendian = bigendian();

	*ppevent = read_trace_init(file_bigendian, host_bigendian);
	if (*ppevent == NULL)
		die("read_trace_init failed");

	read_or_die(buf, 1);
	long_size = buf[0];

	page_size = read4(*ppevent);

	read_header_files(*ppevent);

	read_ftrace_files(*ppevent);
	read_event_files(*ppevent);
	read_proc_kallsyms(*ppevent);
	read_ftrace_printk(*ppevent);

	size = calc_data_size - 1;
	calc_data_size = 0;
	repipe = false;

	if (show_funcs) {
		pevent_print_funcs(*ppevent);
		return size;
	}
	if (show_printk) {
		pevent_print_printk(*ppevent);
		return size;
	}

	return size;
}