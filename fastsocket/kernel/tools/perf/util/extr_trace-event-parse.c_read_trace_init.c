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
struct pevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PEVENT_NSEC_OUTPUT ; 
 struct pevent* pevent_alloc () ; 
 int /*<<< orphan*/  pevent_set_file_bigendian (struct pevent*,int) ; 
 int /*<<< orphan*/  pevent_set_flag (struct pevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pevent_set_host_bigendian (struct pevent*,int) ; 

struct pevent *read_trace_init(int file_bigendian, int host_bigendian)
{
	struct pevent *pevent = pevent_alloc();

	if (pevent != NULL) {
		pevent_set_flag(pevent, PEVENT_NSEC_OUTPUT);
		pevent_set_file_bigendian(pevent, file_bigendian);
		pevent_set_host_bigendian(pevent, host_bigendian);
	}

	return pevent;
}