#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pipe_output; } ;
struct perf_record {int /*<<< orphan*/  evlist; TYPE_3__* session; int /*<<< orphan*/  output; int /*<<< orphan*/  no_buildid; scalar_t__ bytes_written; TYPE_1__ opts; } ;
struct TYPE_6__ {int /*<<< orphan*/  data_size; } ;
struct TYPE_7__ {TYPE_2__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_evlist__delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_session__delete (TYPE_3__*) ; 
 int /*<<< orphan*/  perf_session__write_header (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_buildids (struct perf_record*) ; 
 int /*<<< orphan*/  symbol__exit () ; 

__attribute__((used)) static void perf_record__exit(int status, void *arg)
{
	struct perf_record *rec = arg;

	if (status != 0)
		return;

	if (!rec->opts.pipe_output) {
		rec->session->header.data_size += rec->bytes_written;

		if (!rec->no_buildid)
			process_buildids(rec);
		perf_session__write_header(rec->session, rec->evlist,
					   rec->output, true);
		perf_session__delete(rec->session);
		perf_evlist__delete(rec->evlist);
		symbol__exit();
	}
}