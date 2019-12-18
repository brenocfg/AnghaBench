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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  PERF_RECORD_COMM 131 
#define  PERF_RECORD_EXIT 130 
#define  PERF_RECORD_FORK 129 
#define  PERF_RECORD_MMAP 128 
 size_t fprintf (int /*<<< orphan*/ *,char*,...) ; 
 size_t perf_event__fprintf_comm (union perf_event*,int /*<<< orphan*/ *) ; 
 size_t perf_event__fprintf_mmap (union perf_event*,int /*<<< orphan*/ *) ; 
 size_t perf_event__fprintf_task (union perf_event*,int /*<<< orphan*/ *) ; 
 char* perf_event__name (int) ; 

size_t perf_event__fprintf(union perf_event *event, FILE *fp)
{
	size_t ret = fprintf(fp, "PERF_RECORD_%s",
			     perf_event__name(event->header.type));

	switch (event->header.type) {
	case PERF_RECORD_COMM:
		ret += perf_event__fprintf_comm(event, fp);
		break;
	case PERF_RECORD_FORK:
	case PERF_RECORD_EXIT:
		ret += perf_event__fprintf_task(event, fp);
		break;
	case PERF_RECORD_MMAP:
		ret += perf_event__fprintf_mmap(event, fp);
		break;
	default:
		ret += fprintf(fp, "\n");
	}

	return ret;
}