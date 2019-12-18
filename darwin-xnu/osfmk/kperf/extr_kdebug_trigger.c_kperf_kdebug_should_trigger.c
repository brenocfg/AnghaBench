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
typedef  size_t uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_2__ {size_t n_debugids; int* debugids; int /*<<< orphan*/  types; } ;

/* Variables and functions */
 scalar_t__ DBG_PERF ; 
 size_t DECODE_TYPE (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ KDBG_EXTRACT_CLASS (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int* debugid_masks ; 
 TYPE_1__* kperf_kdebug_filter ; 

boolean_t
kperf_kdebug_should_trigger(uint32_t debugid)
{
	/* ignore kperf events */
	if (KDBG_EXTRACT_CLASS(debugid) == DBG_PERF) {
		return FALSE;
	}

	/*
	 * Search linearly through list of debugids and masks.  If the filter
	 * gets larger than 128 bytes, change this to either a binary search or
	 * a sparse bitmap on the uint32_t range, depending on the new size.
	 */
	for (uint8_t i = 0; i < kperf_kdebug_filter->n_debugids; i++) {
		uint32_t check_debugid =
			kperf_kdebug_filter->debugids[i];
		uint32_t mask = debugid_masks[DECODE_TYPE(kperf_kdebug_filter->types, i)];

		if ((debugid & mask) == check_debugid) {
			return TRUE;
		}
	}

	return FALSE;
}