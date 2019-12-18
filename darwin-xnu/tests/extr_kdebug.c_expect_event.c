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
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct trace_point {int const debugid; int /*<<< orphan*/  arg1; } ;

/* Variables and functions */
 int const KDBG_EVENTID_MASK ; 
 int /*<<< orphan*/  T_EXPECT_EQ (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_LOG (char*,char const*,int const) ; 
 int /*<<< orphan*/  T_QUIET ; 

__attribute__((used)) static void
expect_event(struct trace_point *tp, const char *name, unsigned int *events,
		const uint32_t *event_ids, size_t event_ids_len)
{
	unsigned int event_idx = *events;
	bool event_found = false;
	size_t i;
	for (i = 0; i < event_ids_len; i++) {
		if (event_ids[i] == (tp->debugid & KDBG_EVENTID_MASK)) {
			T_LOG("found %s event 0x%x", name, tp->debugid);
			event_found = true;
		}
	}

	if (!event_found) {
		return;
	}

	*events += 1;
	for (i = 0; i < event_idx; i++) {
		T_QUIET; T_EXPECT_EQ(((uint64_t *)&tp->arg1)[i], (uint64_t)i + 1,
				NULL);
	}
	for (; i < 4; i++) {
		T_QUIET; T_EXPECT_EQ(((uint64_t *)&tp->arg1)[i], (uint64_t)0, NULL);
	}
}