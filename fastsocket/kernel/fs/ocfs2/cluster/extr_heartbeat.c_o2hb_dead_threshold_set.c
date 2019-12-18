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

/* Variables and functions */
 unsigned int O2HB_MIN_DEAD_THRESHOLD ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  o2hb_all_regions ; 
 unsigned int o2hb_dead_threshold ; 
 int /*<<< orphan*/  o2hb_live_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void o2hb_dead_threshold_set(unsigned int threshold)
{
	if (threshold > O2HB_MIN_DEAD_THRESHOLD) {
		spin_lock(&o2hb_live_lock);
		if (list_empty(&o2hb_all_regions))
			o2hb_dead_threshold = threshold;
		spin_unlock(&o2hb_live_lock);
	}
}