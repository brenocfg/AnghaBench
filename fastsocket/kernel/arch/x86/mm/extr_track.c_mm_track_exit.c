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
struct TYPE_2__ {int /*<<< orphan*/ * vector; scalar_t__ bitcnt; scalar_t__ active; } ;

/* Variables and functions */
 TYPE_1__ mm_tracking_struct ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

void mm_track_exit(void)
{
	/*
	 * Inhibit the use of the tracking functions.
	 * This should have already been done, but just in case.
	 */
	mm_tracking_struct.active = 0;
	mm_tracking_struct.bitcnt = 0;

	if (mm_tracking_struct.vector != NULL)
		vfree(mm_tracking_struct.vector);
}