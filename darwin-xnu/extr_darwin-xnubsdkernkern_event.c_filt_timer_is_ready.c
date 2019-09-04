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
struct knote {scalar_t__* kn_ext; int kn_sfflags; } ;

/* Variables and functions */
 int NOTE_MACH_CONTINUOUS_TIME ; 
 scalar_t__ mach_absolute_time () ; 
 scalar_t__ mach_continuous_time () ; 

__attribute__((used)) static bool
filt_timer_is_ready(struct knote *kn)
{
	uint64_t now, deadline = kn->kn_ext[0];

	if (deadline == 0) {
		return true;
	}

	if (kn->kn_sfflags & NOTE_MACH_CONTINUOUS_TIME) {
		now = mach_continuous_time();
	} else {
		now = mach_absolute_time();
	}
	return deadline <= now;
}