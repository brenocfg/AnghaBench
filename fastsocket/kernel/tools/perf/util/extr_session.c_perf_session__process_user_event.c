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
struct TYPE_2__ {int type; } ;
union perf_event {TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  u64 ;
struct perf_tool {int (* attr ) (struct perf_tool*,union perf_event*,int /*<<< orphan*/ *) ;int (* event_type ) (struct perf_tool*,union perf_event*) ;int (* tracing_data ) (struct perf_tool*,union perf_event*,struct perf_session*) ;int (* build_id ) (struct perf_tool*,union perf_event*,struct perf_session*) ;int (* finished_round ) (struct perf_tool*,union perf_event*,struct perf_session*) ;} ;
struct perf_session {int /*<<< orphan*/  fd; int /*<<< orphan*/  evlist; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PERF_RECORD_FINISHED_ROUND 132 
#define  PERF_RECORD_HEADER_ATTR 131 
#define  PERF_RECORD_HEADER_BUILD_ID 130 
#define  PERF_RECORD_HEADER_EVENT_TYPE 129 
#define  PERF_RECORD_HEADER_TRACING_DATA 128 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  dump_event (struct perf_session*,union perf_event*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_session__set_id_hdr_size (struct perf_session*) ; 
 int stub1 (struct perf_tool*,union perf_event*,int /*<<< orphan*/ *) ; 
 int stub2 (struct perf_tool*,union perf_event*) ; 
 int stub3 (struct perf_tool*,union perf_event*,struct perf_session*) ; 
 int stub4 (struct perf_tool*,union perf_event*,struct perf_session*) ; 
 int stub5 (struct perf_tool*,union perf_event*,struct perf_session*) ; 

__attribute__((used)) static int perf_session__process_user_event(struct perf_session *session, union perf_event *event,
					    struct perf_tool *tool, u64 file_offset)
{
	int err;

	dump_event(session, event, file_offset, NULL);

	/* These events are processed right away */
	switch (event->header.type) {
	case PERF_RECORD_HEADER_ATTR:
		err = tool->attr(tool, event, &session->evlist);
		if (err == 0)
			perf_session__set_id_hdr_size(session);
		return err;
	case PERF_RECORD_HEADER_EVENT_TYPE:
		return tool->event_type(tool, event);
	case PERF_RECORD_HEADER_TRACING_DATA:
		/* setup for reading amidst mmap */
		lseek(session->fd, file_offset, SEEK_SET);
		return tool->tracing_data(tool, event, session);
	case PERF_RECORD_HEADER_BUILD_ID:
		return tool->build_id(tool, event, session);
	case PERF_RECORD_FINISHED_ROUND:
		return tool->finished_round(tool, event, session);
	default:
		return -EINVAL;
	}
}