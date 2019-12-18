#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct perf_trace_event_type {int dummy; } ;
struct perf_header {int frozen; int /*<<< orphan*/  data_offset; scalar_t__ needs_swap; } ;
struct perf_session {int /*<<< orphan*/ * evlist; int /*<<< orphan*/  pevent; scalar_t__ fd_pipe; struct perf_header header; } ;
struct TYPE_7__ {int size; int /*<<< orphan*/  offset; } ;
struct TYPE_5__ {int size; int /*<<< orphan*/  offset; } ;
struct perf_file_header {int attr_size; TYPE_3__ event_types; TYPE_1__ attrs; } ;
struct TYPE_6__ {int size; int /*<<< orphan*/  offset; } ;
struct perf_file_attr {TYPE_2__ ids; int /*<<< orphan*/  attr; } ;
struct perf_evsel {scalar_t__ needs_swap; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  f_id ;
struct TYPE_8__ {int nr_events; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int errno ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  perf_event__attr_swap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_evlist__add (int /*<<< orphan*/ *,struct perf_evsel*) ; 
 int /*<<< orphan*/  perf_evlist__delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_evlist__id_add (int /*<<< orphan*/ *,struct perf_evsel*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * perf_evlist__new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ perf_evlist__prepare_tracepoint_events (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ perf_evsel__alloc_id (struct perf_evsel*,int,int) ; 
 struct perf_evsel* perf_evsel__new (int /*<<< orphan*/ *,int) ; 
 scalar_t__ perf_file_header__read (struct perf_file_header*,struct perf_header*,int) ; 
 int /*<<< orphan*/  perf_file_section__process ; 
 scalar_t__ perf_header__getbuffer64 (struct perf_header*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  perf_header__process_sections (struct perf_header*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int perf_header__read_pipe (struct perf_session*,int) ; 
 scalar_t__ read_attr (int,struct perf_header*,struct perf_file_attr*) ; 
 TYPE_4__ symbol_conf ; 
 int trace_event_count ; 
 int /*<<< orphan*/ * trace_events ; 

int perf_session__read_header(struct perf_session *session, int fd)
{
	struct perf_header *header = &session->header;
	struct perf_file_header	f_header;
	struct perf_file_attr	f_attr;
	u64			f_id;
	int nr_attrs, nr_ids, i, j;

	session->evlist = perf_evlist__new(NULL, NULL);
	if (session->evlist == NULL)
		return -ENOMEM;

	if (session->fd_pipe)
		return perf_header__read_pipe(session, fd);

	if (perf_file_header__read(&f_header, header, fd) < 0)
		return -EINVAL;

	nr_attrs = f_header.attrs.size / f_header.attr_size;
	lseek(fd, f_header.attrs.offset, SEEK_SET);

	for (i = 0; i < nr_attrs; i++) {
		struct perf_evsel *evsel;
		off_t tmp;

		if (read_attr(fd, header, &f_attr) < 0)
			goto out_errno;

		if (header->needs_swap)
			perf_event__attr_swap(&f_attr.attr);

		tmp = lseek(fd, 0, SEEK_CUR);
		evsel = perf_evsel__new(&f_attr.attr, i);

		if (evsel == NULL)
			goto out_delete_evlist;

		evsel->needs_swap = header->needs_swap;
		/*
		 * Do it before so that if perf_evsel__alloc_id fails, this
		 * entry gets purged too at perf_evlist__delete().
		 */
		perf_evlist__add(session->evlist, evsel);

		nr_ids = f_attr.ids.size / sizeof(u64);
		/*
		 * We don't have the cpu and thread maps on the header, so
		 * for allocating the perf_sample_id table we fake 1 cpu and
		 * hattr->ids threads.
		 */
		if (perf_evsel__alloc_id(evsel, 1, nr_ids))
			goto out_delete_evlist;

		lseek(fd, f_attr.ids.offset, SEEK_SET);

		for (j = 0; j < nr_ids; j++) {
			if (perf_header__getbuffer64(header, fd, &f_id, sizeof(f_id)))
				goto out_errno;

			perf_evlist__id_add(session->evlist, evsel, 0, j, f_id);
		}

		lseek(fd, tmp, SEEK_SET);
	}

	symbol_conf.nr_events = nr_attrs;

	if (f_header.event_types.size) {
		lseek(fd, f_header.event_types.offset, SEEK_SET);
		trace_events = malloc(f_header.event_types.size);
		if (trace_events == NULL)
			return -ENOMEM;
		if (perf_header__getbuffer64(header, fd, trace_events,
					     f_header.event_types.size))
			goto out_errno;
		trace_event_count =  f_header.event_types.size / sizeof(struct perf_trace_event_type);
	}

	perf_header__process_sections(header, fd, &session->pevent,
				      perf_file_section__process);

	lseek(fd, header->data_offset, SEEK_SET);

	if (perf_evlist__prepare_tracepoint_events(session->evlist,
						   session->pevent))
		goto out_delete_evlist;

	header->frozen = 1;
	return 0;
out_errno:
	return -errno;

out_delete_evlist:
	perf_evlist__delete(session->evlist);
	session->evlist = NULL;
	return -ENOMEM;
}