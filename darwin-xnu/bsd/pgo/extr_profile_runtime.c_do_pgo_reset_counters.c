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
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  OSKextResetPgoCounters () ; 
 int /*<<< orphan*/  __pgo_hib_CountersEnd ; 
 int /*<<< orphan*/  __pgo_hib_CountersStart ; 
 scalar_t__ kdp_pgo_reset_counters ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,uintptr_t) ; 

kern_return_t do_pgo_reset_counters()
{
#ifdef PROFILE
    memset(&__pgo_hib_CountersStart, 0,
           ((uintptr_t)(&__pgo_hib_CountersEnd)) - ((uintptr_t)(&__pgo_hib_CountersStart)));
#endif
    OSKextResetPgoCounters();
    kdp_pgo_reset_counters = 0;
    return KERN_SUCCESS;
}