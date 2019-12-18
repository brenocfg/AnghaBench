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
struct tracing_data {int temp; scalar_t__ size; int /*<<< orphan*/  temp_file; } ;
struct tracepoint_path {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 struct tracepoint_path* get_tracepoints_path (struct list_head*) ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tracing_data* malloc_or_die (int) ; 
 int /*<<< orphan*/  mkstemp (int /*<<< orphan*/ ) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int output_fd ; 
 int /*<<< orphan*/  put_tracepoints_path (struct tracepoint_path*) ; 
 int /*<<< orphan*/  read_event_files (struct tracepoint_path*) ; 
 int /*<<< orphan*/  read_ftrace_files (struct tracepoint_path*) ; 
 int /*<<< orphan*/  read_ftrace_printk () ; 
 int /*<<< orphan*/  read_header_files () ; 
 int /*<<< orphan*/  read_proc_kallsyms () ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  tracing_data_header () ; 

struct tracing_data *tracing_data_get(struct list_head *pattrs,
				      int fd, bool temp)
{
	struct tracepoint_path *tps;
	struct tracing_data *tdata;

	output_fd = fd;

	tps = get_tracepoints_path(pattrs);
	if (!tps)
		return NULL;

	tdata = malloc_or_die(sizeof(*tdata));
	tdata->temp = temp;
	tdata->size = 0;

	if (temp) {
		int temp_fd;

		snprintf(tdata->temp_file, sizeof(tdata->temp_file),
			 "/tmp/perf-XXXXXX");
		if (!mkstemp(tdata->temp_file))
			die("Can't make temp file");

		temp_fd = open(tdata->temp_file, O_RDWR);
		if (temp_fd < 0)
			die("Can't read '%s'", tdata->temp_file);

		/*
		 * Set the temp file the default output, so all the
		 * tracing data are stored into it.
		 */
		output_fd = temp_fd;
	}

	tracing_data_header();
	read_header_files();
	read_ftrace_files(tps);
	read_event_files(tps);
	read_proc_kallsyms();
	read_ftrace_printk();

	/*
	 * All tracing data are stored by now, we can restore
	 * the default output file in case we used temp file.
	 */
	if (temp) {
		tdata->size = lseek(output_fd, 0, SEEK_CUR);
		close(output_fd);
		output_fd = fd;
	}

	put_tracepoints_path(tps);
	return tdata;
}