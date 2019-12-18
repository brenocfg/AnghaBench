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
struct uwb_rc {scalar_t__ active_pals; int beaconing_forced; } ;

/* Variables and functions */

__attribute__((used)) static int uwb_radio_select_channel(struct uwb_rc *rc)
{
	/*
	 * Default to channel 9 (BG1, TFC1) unless the user has
	 * selected a specific channel or there are no active PALs.
	 */
	if (rc->active_pals == 0)
		return -1;
	if (rc->beaconing_forced)
		return rc->beaconing_forced;
	return 9;
}