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
struct TYPE_2__ {int size; } ;
union perf_event {TYPE_1__ header; } ;
typedef  int u64 ;

/* Variables and functions */

__attribute__((used)) static bool sample_overlap(const union perf_event *event,
			   const void *offset, u64 size)
{
	const void *base = event;

	if (offset + size > base + event->header.size)
		return true;

	return false;
}