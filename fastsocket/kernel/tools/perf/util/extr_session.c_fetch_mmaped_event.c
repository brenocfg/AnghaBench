#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int size; } ;
union perf_event {TYPE_2__ header; } ;
typedef  int u64 ;
struct TYPE_3__ {scalar_t__ needs_swap; } ;
struct perf_session {TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_event_header__bswap (TYPE_2__*) ; 

__attribute__((used)) static union perf_event *
fetch_mmaped_event(struct perf_session *session,
		   u64 head, size_t mmap_size, char *buf)
{
	union perf_event *event;

	/*
	 * Ensure we have enough space remaining to read
	 * the size of the event in the headers.
	 */
	if (head + sizeof(event->header) > mmap_size)
		return NULL;

	event = (union perf_event *)(buf + head);

	if (session->header.needs_swap)
		perf_event_header__bswap(&event->header);

	if (head + event->header.size > mmap_size)
		return NULL;

	return event;
}