#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {scalar_t__ dtrd_action; } ;
typedef  TYPE_1__ dtrace_recdesc_t ;
struct TYPE_6__ {scalar_t__ dtpda_data; } ;
typedef  TYPE_2__ dtrace_probedata_t ;
typedef  scalar_t__ dtrace_actkind_t ;

/* Variables and functions */
 scalar_t__ DTRACEACT_EXIT ; 
 int DTRACE_CONSUME_NEXT ; 
 int DTRACE_CONSUME_THIS ; 
 int /*<<< orphan*/  g_quiet ; 
 int /*<<< orphan*/  g_status ; 
 int /*<<< orphan*/  oprintf (char*) ; 

__attribute__((used)) static int
chewrec(const dtrace_probedata_t *data, const dtrace_recdesc_t *rec, void *arg)
{
	dtrace_actkind_t act;
	uintptr_t addr;

	if (rec == NULL) {
		/*
		 * We have processed the final record; output the newline if
		 * we're not in quiet mode.
		 */
		if (!g_quiet)
			oprintf("\n");

		return (DTRACE_CONSUME_NEXT);
	}

	act = rec->dtrd_action;
	addr = (uintptr_t)data->dtpda_data;

	if (act == DTRACEACT_EXIT) {
		g_status = *((uint32_t *)addr);
		return (DTRACE_CONSUME_NEXT);
	}

	return (DTRACE_CONSUME_THIS);
}