#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pid; } ;
struct TYPE_5__ {int /*<<< orphan*/  pid; } ;
struct TYPE_4__ {scalar_t__ misc; scalar_t__ type; } ;
union perf_event {TYPE_3__ ip; TYPE_2__ mmap; TYPE_1__ header; } ;
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct perf_session {int dummy; } ;
struct machine {int dummy; } ;

/* Variables and functions */
 scalar_t__ PERF_RECORD_MISC_CPUMODE_MASK ; 
 scalar_t__ const PERF_RECORD_MISC_GUEST_KERNEL ; 
 scalar_t__ const PERF_RECORD_MISC_GUEST_USER ; 
 scalar_t__ PERF_RECORD_MMAP ; 
 scalar_t__ perf_guest ; 
 struct machine* perf_session__find_host_machine (struct perf_session*) ; 
 struct machine* perf_session__findnew_machine (struct perf_session*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct machine *
	perf_session__find_machine_for_cpumode(struct perf_session *session,
					       union perf_event *event)
{
	const u8 cpumode = event->header.misc & PERF_RECORD_MISC_CPUMODE_MASK;

	if (perf_guest &&
	    ((cpumode == PERF_RECORD_MISC_GUEST_KERNEL) ||
	     (cpumode == PERF_RECORD_MISC_GUEST_USER))) {
		u32 pid;

		if (event->header.type == PERF_RECORD_MMAP)
			pid = event->mmap.pid;
		else
			pid = event->ip.pid;

		return perf_session__findnew_machine(session, pid);
	}

	return perf_session__find_host_machine(session);
}