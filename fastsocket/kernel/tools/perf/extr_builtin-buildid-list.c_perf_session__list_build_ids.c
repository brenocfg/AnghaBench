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
struct perf_session {scalar_t__ fd_pipe; int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  build_id__mark_dso_hit_ops ; 
 scalar_t__ filename__fprintf_build_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_name ; 
 int /*<<< orphan*/  perf_session__delete (struct perf_session*) ; 
 int /*<<< orphan*/  perf_session__fprintf_dsos_buildid (struct perf_session*,int /*<<< orphan*/ ,int) ; 
 struct perf_session* perf_session__new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_session__process_events (struct perf_session*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  symbol__elf_init () ; 

__attribute__((used)) static int perf_session__list_build_ids(bool force, bool with_hits)
{
	struct perf_session *session;

	symbol__elf_init();

	session = perf_session__new(input_name, O_RDONLY, force, false,
				    &build_id__mark_dso_hit_ops);
	if (session == NULL)
		return -1;

	/*
	 * See if this is an ELF file first:
	 */
	if (filename__fprintf_build_id(session->filename, stdout))
		goto out;

	/*
	 * in pipe-mode, the only way to get the buildids is to parse
	 * the record stream. Buildids are stored as RECORD_HEADER_BUILD_ID
	 */
	if (with_hits || session->fd_pipe)
		perf_session__process_events(session, &build_id__mark_dso_hit_ops);

	perf_session__fprintf_dsos_buildid(session, stdout, with_hits);
out:
	perf_session__delete(session);
	return 0;
}