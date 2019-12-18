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
struct pevent {int header_page_ts_size; int header_page_size_size; int header_page_data_offset; int old_format; int header_page_ts_offset; int header_page_size_offset; int header_page_overwrite; int header_page_data_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_input_buf (char*,unsigned long) ; 
 int /*<<< orphan*/  parse_header_field (char*,int*,int*,int) ; 

int pevent_parse_header_page(struct pevent *pevent, char *buf, unsigned long size,
			     int long_size)
{
	int ignore;

	if (!size) {
		/*
		 * Old kernels did not have header page info.
		 * Sorry but we just use what we find here in user space.
		 */
		pevent->header_page_ts_size = sizeof(long long);
		pevent->header_page_size_size = long_size;
		pevent->header_page_data_offset = sizeof(long long) + long_size;
		pevent->old_format = 1;
		return -1;
	}
	init_input_buf(buf, size);

	parse_header_field("timestamp", &pevent->header_page_ts_offset,
			   &pevent->header_page_ts_size, 1);
	parse_header_field("commit", &pevent->header_page_size_offset,
			   &pevent->header_page_size_size, 1);
	parse_header_field("overwrite", &pevent->header_page_overwrite,
			   &ignore, 0);
	parse_header_field("data", &pevent->header_page_data_offset,
			   &pevent->header_page_data_size, 1);

	return 0;
}