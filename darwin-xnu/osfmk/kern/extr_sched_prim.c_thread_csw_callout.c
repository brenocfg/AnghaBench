#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  perfcontrol_event ;
struct TYPE_6__ {int state; int /*<<< orphan*/  same_pri_latency; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTEXT_SWITCH ; 
 int /*<<< orphan*/  IDLE ; 
 int TH_IDLE ; 
 int /*<<< orphan*/  machine_switch_perfcontrol_context (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static void
thread_csw_callout(
	thread_t	    old,
	thread_t	    new,
	uint64_t	    timestamp)
{
	perfcontrol_event event = (new->state & TH_IDLE) ? IDLE : CONTEXT_SWITCH;
	uint64_t same_pri_latency = (new->state & TH_IDLE) ? 0 : new->same_pri_latency;
	machine_switch_perfcontrol_context(event, timestamp, 0, 
		same_pri_latency, old, new);
}