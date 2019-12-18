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
struct stat {scalar_t__ st_uid; scalar_t__ st_size; } ;
struct perf_session {int fd_pipe; int fd; scalar_t__ size; int /*<<< orphan*/  evlist; int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int STDIN_FILENO ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ geteuid () ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_evlist__valid_sample_id_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_evlist__valid_sample_type (int /*<<< orphan*/ ) ; 
 scalar_t__ perf_session__read_header (struct perf_session*,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static int perf_session__open(struct perf_session *self, bool force)
{
	struct stat input_stat;

	if (!strcmp(self->filename, "-")) {
		self->fd_pipe = true;
		self->fd = STDIN_FILENO;

		if (perf_session__read_header(self, self->fd) < 0)
			pr_err("incompatible file format (rerun with -v to learn more)");

		return 0;
	}

	self->fd = open(self->filename, O_RDONLY);
	if (self->fd < 0) {
		int err = errno;

		pr_err("failed to open %s: %s", self->filename, strerror(err));
		if (err == ENOENT && !strcmp(self->filename, "perf.data"))
			pr_err("  (try 'perf record' first)");
		pr_err("\n");
		return -errno;
	}

	if (fstat(self->fd, &input_stat) < 0)
		goto out_close;

	if (!force && input_stat.st_uid && (input_stat.st_uid != geteuid())) {
		pr_err("file %s not owned by current user or root\n",
		       self->filename);
		goto out_close;
	}

	if (!input_stat.st_size) {
		pr_info("zero-sized file (%s), nothing to do!\n",
			self->filename);
		goto out_close;
	}

	if (perf_session__read_header(self, self->fd) < 0) {
		pr_err("incompatible file format (rerun with -v to learn more)");
		goto out_close;
	}

	if (!perf_evlist__valid_sample_type(self->evlist)) {
		pr_err("non matching sample_type");
		goto out_close;
	}

	if (!perf_evlist__valid_sample_id_all(self->evlist)) {
		pr_err("non matching sample_id_all");
		goto out_close;
	}

	self->size = input_stat.st_size;
	return 0;

out_close:
	close(self->fd);
	self->fd = -1;
	return -1;
}