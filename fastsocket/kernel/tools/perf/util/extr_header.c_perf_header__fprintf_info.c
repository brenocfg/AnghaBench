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
struct perf_header {int dummy; } ;
struct perf_session {int fd; struct perf_header header; } ;
struct header_print_data {int full; int /*<<< orphan*/ * fp; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  perf_file_section__fprintf_info ; 
 int /*<<< orphan*/  perf_header__process_sections (struct perf_header*,int,struct header_print_data*,int /*<<< orphan*/ ) ; 

int perf_header__fprintf_info(struct perf_session *session, FILE *fp, bool full)
{
	struct header_print_data hd;
	struct perf_header *header = &session->header;
	int fd = session->fd;
	hd.fp = fp;
	hd.full = full;

	perf_header__process_sections(header, fd, &hd,
				      perf_file_section__fprintf_info);
	return 0;
}