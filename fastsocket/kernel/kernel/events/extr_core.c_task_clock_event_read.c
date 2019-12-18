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
typedef  scalar_t__ u64 ;
struct perf_event {TYPE_1__* ctx; } ;
struct TYPE_2__ {scalar_t__ time; scalar_t__ timestamp; } ;

/* Variables and functions */
 scalar_t__ perf_clock () ; 
 int /*<<< orphan*/  task_clock_event_update (struct perf_event*,scalar_t__) ; 

__attribute__((used)) static void task_clock_event_read(struct perf_event *event)
{
	u64 now = perf_clock();
	u64 delta = now - event->ctx->timestamp;
	u64 time = event->ctx->time + delta;

	task_clock_event_update(event, time);
}