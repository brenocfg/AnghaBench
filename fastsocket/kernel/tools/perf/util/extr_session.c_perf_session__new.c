#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct perf_tool {int ordered_samples; scalar_t__ ordering_requires_timestamps; } ;
struct TYPE_2__ {int /*<<< orphan*/  to_free; int /*<<< orphan*/  sample_cache; int /*<<< orphan*/  samples; } ;
struct perf_session {int mmap_window; int repipe; int /*<<< orphan*/  evlist; int /*<<< orphan*/  hists; int /*<<< orphan*/  host_machine; TYPE_1__ ordered_samples; int /*<<< orphan*/  machines; int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_KERNEL_ID ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int O_RDONLY ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 int ULLONG_MAX ; 
 int /*<<< orphan*/  dump_printf (char*) ; 
 int /*<<< orphan*/  fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  hists__init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  machine__init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  perf_evlist__sample_id_all (int /*<<< orphan*/ ) ; 
 scalar_t__ perf_session__create_kernel_maps (struct perf_session*) ; 
 int /*<<< orphan*/  perf_session__delete (struct perf_session*) ; 
 scalar_t__ perf_session__open (struct perf_session*,int) ; 
 int /*<<< orphan*/  perf_session__set_id_hdr_size (struct perf_session*) ; 
 size_t strlen (char const*) ; 
 struct perf_session* zalloc (int) ; 

struct perf_session *perf_session__new(const char *filename, int mode,
				       bool force, bool repipe,
				       struct perf_tool *tool)
{
	struct perf_session *self;
	struct stat st;
	size_t len;

	if (!filename || !strlen(filename)) {
		if (!fstat(STDIN_FILENO, &st) && S_ISFIFO(st.st_mode))
			filename = "-";
		else
			filename = "perf.data";
	}

	len = strlen(filename);
	self = zalloc(sizeof(*self) + len);

	if (self == NULL)
		goto out;

	memcpy(self->filename, filename, len);
	/*
	 * On 64bit we can mmap the data file in one go. No need for tiny mmap
	 * slices. On 32bit we use 32MB.
	 */
#if BITS_PER_LONG == 64
	self->mmap_window = ULLONG_MAX;
#else
	self->mmap_window = 32 * 1024 * 1024ULL;
#endif
	self->machines = RB_ROOT;
	self->repipe = repipe;
	INIT_LIST_HEAD(&self->ordered_samples.samples);
	INIT_LIST_HEAD(&self->ordered_samples.sample_cache);
	INIT_LIST_HEAD(&self->ordered_samples.to_free);
	machine__init(&self->host_machine, "", HOST_KERNEL_ID);
	hists__init(&self->hists);

	if (mode == O_RDONLY) {
		if (perf_session__open(self, force) < 0)
			goto out_delete;
		perf_session__set_id_hdr_size(self);
	} else if (mode == O_WRONLY) {
		/*
		 * In O_RDONLY mode this will be performed when reading the
		 * kernel MMAP event, in perf_event__process_mmap().
		 */
		if (perf_session__create_kernel_maps(self) < 0)
			goto out_delete;
	}

	if (tool && tool->ordering_requires_timestamps &&
	    tool->ordered_samples && !perf_evlist__sample_id_all(self->evlist)) {
		dump_printf("WARNING: No sample_id_all support, falling back to unordered processing\n");
		tool->ordered_samples = false;
	}

out:
	return self;
out_delete:
	perf_session__delete(self);
	return NULL;
}